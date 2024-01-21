// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
#include "OmokPlayerState.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Omok/OmokGameModeBase.h"
#include "Omok/Omok.h"
#include "Omok/Board/OmokBoard.h"
#include "Omok/Board/OmokNode.h"

// Sets default values
AOmokPlayer::AOmokPlayer(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer),
	BoardLocationFromPlayer(200.f, 100.f)
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

// Called when the game starts or when spawned
void AOmokPlayer::BeginPlay()
{
	Super::BeginPlay();

	//바둑판, 바둑알은 플레이어 로컬 머신에 하나씩만 존재해야 한다.
	if(false == IsLocallyControlled())
	{
		return;
	}

	//바둑판은 플레이레벨에만 필요.
	if(TEXT("PlayLevel") != GetWorld()->GetName())
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

	Board = GetWorld()->SpawnActor<AOmokBoard>(BoardSpawnLocation, BoardSpawnRotation, BoardSpawnParams);

	for(TObjectPtr<AOmokNode> Node : Board->GetAllNodes())
	{
		Node->GetNodeMesh()->OnBeginCursorOver.AddDynamic(this, &AOmokPlayer::OnBeginCursorOver_SetClearColor);
		Node->GetNodeMesh()->OnEndCursorOver.AddDynamic(this, &AOmokPlayer::OnEndCursorOver_ReturnColor);
		Node->GetNodeMesh()->OnClicked.AddDynamic(this, &AOmokPlayer::OnClicked_FixColor);
	}
}

void AOmokPlayer::OnBeginCursorOver_SetClearColor(UPrimitiveComponent* TouchedComponent)
{
	CastChecked<AOmokNode>(TouchedComponent->GetOwner())->SetClearColor(
		GetPlayerStateChecked<AOmokPlayerState>()->GetbWhite()
	);
}

void AOmokPlayer::OnEndCursorOver_ReturnColor(UPrimitiveComponent* TouchedComponent)
{
	CastChecked<AOmokNode>(TouchedComponent->GetOwner())->ReturnColor();
}

void AOmokPlayer::OnClicked_FixColor(UPrimitiveComponent* ClickedComponent, const FKey PressedButton)
{
	//우클릭은 무시.
	if(EKeys::RightMouseButton == PressedButton)
	{
		return;
	}

	TObjectPtr<AOmokNode> OmokNode = CastChecked<AOmokNode>(ClickedComponent->GetOwner());
	TObjectPtr<AOmokPlayerState> OmokPlayerState = GetPlayerStateChecked<AOmokPlayerState>();

	OmokNode->FixColor(OmokPlayerState->GetbWhite());

	OmokPlayerState->ServerRPC_DeliverNodeCoord(OmokNode->GetCoordinate());
}
