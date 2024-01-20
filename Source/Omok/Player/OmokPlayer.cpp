// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
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

	//static ConstructorHelpers::FObjectFinder<UInputAction> OmokCheckMouseLocationRef(
	//	TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/IA_OmokCheckMouseLocation.IA_OmokCheckMouseLocation'")
	//);
	//ensure(OmokCheckMouseLocationRef.Succeeded());
	//OmokCheckMouseLocation = OmokCheckMouseLocationRef.Object;

	//static ConstructorHelpers::FObjectFinder<UInputAction> OmokMouseClickRef(
	//	TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/IA_OmokMouseClick.IA_OmokMouseClick'")
	//);
	//ensure(OmokMouseClickRef.Succeeded());
	//OmokMouseClick = OmokMouseClickRef.Object;


	bReplicates = true;
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

	//바둑판, 바둑알은 유저 로컬 머신에 하나씩만 존재해야 한다.
	if(false == IsLocallyControlled())
	{
		return;
	}

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
}

void AOmokPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AOmokPlayer::OnBeginCursorOverlap_ChangeColor(UPrimitiveComponent* ClickedComponent)
{
	//CastChecked<AOmokNode>(ClickedComponent)
}

void AOmokPlayer::OnEndCursorOverlap_ReturnColor(UPrimitiveComponent* ClickedComponent)
{
}

void AOmokPlayer::OnClicked_FixColor(UPrimitiveComponent* ClickedComponent, const FKey PressedButton)
{
}

//void AOmokPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
//
//	//InputComponent->BindAction(OmokCheckMouseLocation, ETriggerEvent::Ongoing, this, );
//	//InputComponent->BindAction(OmokMouseClick, ETriggerEvent::Triggered, this, );
//}
