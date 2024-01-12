// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AOmokPlayer::AOmokPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OmokPlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OmokCamera"));
	OmokPlayerCamera->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));
	OmokPlayerCamera->SetupAttachment(this->RootComponent);

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
	
}

// Called when the game starts or when spawned
void AOmokPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AOmokPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

// Called every frame
void AOmokPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
