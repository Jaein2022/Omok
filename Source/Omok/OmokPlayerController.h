// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmokPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API AOmokPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOmokPlayerController();

	//virtual void BeginPlay() override;

	FORCEINLINE void SetIsWhite(const bool InIsWhite) { this->IsWhite = InIsWhite; }
	FORCEINLINE bool GetIsWhite() const { return IsWhite; }

	//virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	//virtual void SetPawn(APawn* InPawn) override;

protected:
	

private:
	bool IsWhite;
};
