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

	FORCEINLINE void SetIsWhite(const bool InIsWhite) { this->IsWhite = InIsWhite; }
	FORCEINLINE bool GetIsWhite() const { return IsWhite; }

protected:
	

private:
	bool IsWhite;

};
