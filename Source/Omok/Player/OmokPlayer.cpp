// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
#include "OmokPlayerState.h"
#include "Camera/CameraComponent.h"
#include "Omok/Omok.h"
#include "Omok/Board/OmokBoard.h"
#include "Omok/Board/OmokNode.h"

// Sets default values
AOmokPlayer::AOmokPlayer(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OmokPlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OmokCamera"));
	OmokPlayerCamera->SetupAttachment(this->RootComponent);
	OmokPlayerCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
}

// Called every frame
void AOmokPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AOmokPlayer::CheckWinningCondition(const FIntVector2& InCoord, const uint8 InbWhite) const
{
	ensure(HasAuthority());

	//InbWhite와 InCoord 좌표의 바둑돌 색은 반드시 같아야 한다.
	if(InbWhite)
	{
		ensure(ENodeColor::White == OmokBoard->GetNode(InCoord)->GetColor());
	}
	else
	{
		ensure(ENodeColor::Black == OmokBoard->GetNode(InCoord)->GetColor());
	}
	
	//로직 변경 예정.

	const int32 X = InCoord.X;
	const int32 Y = InCoord.Y;

	//이번 돌에서 연결되는 직선들 중 가장 긴 것의 길이.
	const int32 LineLength = 1 + FMath::Max(
		TArray<int32>({
			OmokBoard->CountSameColorNodes(X, Y + 1, InbWhite, 0, 1) + OmokBoard->CountSameColorNodes(X, Y - 1, InbWhite, 0, -1),
			//수평 체크.

			OmokBoard->CountSameColorNodes(X + 1, Y, InbWhite, 1, 0) + OmokBoard->CountSameColorNodes(X - 1, Y, InbWhite, -1, 0),
			//수직 체크.

			OmokBoard->CountSameColorNodes(X + 1, Y + 1, InbWhite, 1, 1) + OmokBoard->CountSameColorNodes(X - 1, Y - 1, InbWhite, -1, -1),
			//사선 / 체크.

			OmokBoard->CountSameColorNodes(X + 1, Y - 1, InbWhite, 1, -1) + OmokBoard->CountSameColorNodes(X - 1, Y + 1, InbWhite, -1, 1)
			//사선 \ 체크.
		})
	);

	//같은색 돌이 WinningCount 이상 연속되면 승리 처리.
	return (WinningCount <= LineLength) ? true : false;
}

void AOmokPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	OmokPlayerState = GetPlayerStateChecked<AOmokPlayerState>();
}

// Called when the game starts or when spawned
void AOmokPlayer::BeginPlay()
{
	Super::BeginPlay();

	//바둑판은 플레이레벨에만 필요.
	if(TEXT("PlayLevel") != GetWorld()->GetName())
	{
		return;
	}

	//바둑판, 바둑알은 플레이어 로컬 머신에 하나씩만 존재해야 한다.
	if(false == IsLocallyControlled())
	{
		return;
	}

	FActorSpawnParameters BoardSpawnParams;
	BoardSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	BoardSpawnParams.Owner = this;

	const FVector BoardSpawnLocation = GetActorLocation() 
		+ (GetActorForwardVector() * BoardLocationFromPlayer.X) 
		+ (-GetActorRightVector() * BoardLocationFromPlayer.Y);

	const FRotator BoardSpawnRotation = GetActorUpVector().Rotation();

	OmokBoard = GetWorld()->SpawnActor<AOmokBoard>(BoardSpawnLocation, BoardSpawnRotation, BoardSpawnParams);

	for(TObjectPtr<AOmokNode> Node : OmokBoard->GetAllNodes())
	{
		Node->OnBeginCursorOver.AddDynamic(this, &AOmokPlayer::OnBeginCursorOver_SetClearColor);
		Node->OnEndCursorOver.AddDynamic(this, &AOmokPlayer::OnEndCursorOver_ReturnColor);
		Node->OnClicked.AddDynamic(this, &AOmokPlayer::OnClicked_FixColor);
	}

	//서버의 플레이어 스테이트 보관.
	if(HasAuthority())	
	{
		OmokPlayerState = GetPlayerStateChecked<AOmokPlayerState>();
	}
}

void AOmokPlayer::OnBeginCursorOver_SetClearColor(AActor* TouchedActor)
{
	//자기 턴이 아니면 입력 무시.
	if(false == OmokPlayerState->IsMyTurn())
	{
		return;
	}

	CastChecked<AOmokNode>(TouchedActor)->SetClearColor(OmokPlayerState->GetbWhite());
}

void AOmokPlayer::OnEndCursorOver_ReturnColor(AActor* TouchedActor)
{
	//자기 턴이 아니면 입력 무시.
	if(false == OmokPlayerState->IsMyTurn())
	{
		return;
	}

	CastChecked<AOmokNode>(TouchedActor)->ReturnColor();
}

void AOmokPlayer::OnClicked_FixColor(AActor* ClickedActor, const FKey PressedButton)
{
	//우클릭은 무시.
	if(EKeys::RightMouseButton == PressedButton)
	{
		return; 
	}

	//자기 턴이 아니면 입력 무시.
	if(false == OmokPlayerState->IsMyTurn())
	{
		return;
	}

	TObjectPtr<AOmokNode> OmokNode = CastChecked<AOmokNode>(ClickedActor);

	OmokNode->FixColor(OmokPlayerState->GetbWhite());
	OmokPlayerState->ServerRPC_DeliverNodeCoord(OmokNode->GetCoordinate());
}
