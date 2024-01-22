// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OmokGameStateBase.generated.h"

UCLASS()
class OMOK_API AOmokGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AOmokGameStateBase();
	
	//전달받은 메세지를 송신자 제외한 나머지 플레이어 스테이트에 배분하는 함수. 서버 전용.
	void DistributeMessage(const FText& InText, const TObjectPtr<class AOmokPlayerState> Sender);

	//플레이어가 놓은 바둑알 위치를 나머지 플레이어 스테이트에 배분하는 함수. 서버 전용.
	void DistributeNodeCoord(const FIntVector2& InCoord, const TObjectPtr<class AOmokPlayerState> Sender);

	virtual void HandleBeginPlay() override;

public:
	FORCEINLINE const uint8 GetCurrentPlayerColor() const { return CurrentPlayerColor; }



protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//
	void ShiftToPlay();

	void ShiftToRest();



public:
	const float PlayTimeLimit = 10.f;	//턴당 플레이 시간.
	const float RestTimeLimit = 3.f;	//턴당 휴식 시간.



private:
	//0: 검은색, 1: 흰색, 2: 누구 차례도 아님.
	UPROPERTY(Replicated)
	uint8 CurrentPlayerColor;	
		
	//0: 검은색, 1: 흰색.
	uint8 PrevPlayerColor;		

	FTimerDelegate PlayTimerDelegate;
	FTimerDelegate RestTimerDelegate;

	FTimerHandle GameStateTimerHandle;

};
