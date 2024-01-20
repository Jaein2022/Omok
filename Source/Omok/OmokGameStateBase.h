// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OmokGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API AOmokGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AOmokGameStateBase();
	
	void DistributeMessage(const FText& InText, const TObjectPtr<class AOmokPlayerState> Sender);


	
protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



private:



};
