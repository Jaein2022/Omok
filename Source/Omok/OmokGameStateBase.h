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
	
	//전달받은 메세지를 송신자 제외한 나머지 플레이어 스테이트에 배분하는 함수. 
	void DistributeMessage(const FText& InText, const TObjectPtr<class AOmokPlayerState> Sender);


	
protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



private:



};
