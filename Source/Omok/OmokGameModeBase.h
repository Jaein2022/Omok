// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmokGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API AOmokGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AOmokGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecond) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> IMC;

};
