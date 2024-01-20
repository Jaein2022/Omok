// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Omok/OmokGameModeBase.h"
#include "Omok/Omok.h"
//#include "OmokPlayerState.h"

// Sets default values
AOmokPlayer::AOmokPlayer()
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
}

void AOmokPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME_CONDITION(AOmokPlayer, bWhite, COND_InitialOnly);
}

//void AOmokPlayer::TestFunction()
//{
//	FOmokDevelopmentSupport::DisplayDebugMessageForActors(
//		this,
//		__FUNCTION__,
//		TEXT("ColorTest"),
//		30.f,
//		bWhite?FColor::White:FColor::Black
//	);
//}

//void AOmokPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
//
//	//InputComponent->BindAction(OmokCheckMouseLocation, ETriggerEvent::Ongoing, this, );
//	//InputComponent->BindAction(OmokMouseClick, ETriggerEvent::Triggered, this, );
//}
