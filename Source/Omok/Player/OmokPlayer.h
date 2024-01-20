﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OmokPlayer.generated.h"

/**
*
*/
UCLASS()
class OMOK_API AOmokPlayer : public APawn
{
	GENERATED_BODY()

	friend class AOmokPlayerController;

public:
	// Sets default values for this pawn's properties
	AOmokPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> OmokPlayerCamera;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	//TObjectPtr<class UInputAction> OmokCheckMouseLocation;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	//TObjectPtr<class UInputAction> OmokMouseClick;



private:



private:

};
