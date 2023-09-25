// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayer.h"
#include "Camera/CameraComponent.h"

// Sets default values
AOmokPlayer::AOmokPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->OmokPlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OmokCamera"));
	this->OmokPlayerCamera->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));
	this->OmokPlayerCamera->SetupAttachment(this->RootComponent);

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
