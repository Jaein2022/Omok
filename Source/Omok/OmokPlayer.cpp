// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AOmokPlayer::AOmokPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->OmokPlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OmokCamera"));
	this->OmokPlayerCamera->SetupAttachment(this->RootComponent);

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseLocationRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/IA_OmokMouseLocation.IA_OmokMouseLocation'")
	);
	ensure(MouseLocationRef.Succeeded());
	this->OmokMouseLocation = MouseLocationRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseClickRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/IA_OmokMouseClick.IA_OmokMouseClick'")
	);
	ensure(MouseClickRef.Succeeded());
	this->OmokMouseClick = MouseClickRef.Object;

	




}

// Called when the game starts or when spawned
void AOmokPlayer::BeginPlay()
{
	Super::BeginPlay();

	


}

// Called every frame
void AOmokPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOmokPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);


	EnhancedInputComponent->BindAction(
		this->OmokMouseLocation,
		ETriggerEvent::Triggered,
		this,
		&AOmokPlayer::RenderPointer
	);
	
	EnhancedInputComponent->BindAction(
		this->OmokMouseClick,
		ETriggerEvent::Triggered,
		this,
		&AOmokPlayer::Click
	);
}

void AOmokPlayer::RenderPointer(const FInputActionValue& Input)
{
	const FVector2D InputVector = Input.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("X: %f, Y: %f"), InputVector.X, InputVector.Y));


}

void AOmokPlayer::Click(const FInputActionValue& Input)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, TEXT("Click!"));
}

