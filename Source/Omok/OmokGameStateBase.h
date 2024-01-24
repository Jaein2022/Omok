// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OmokGameStateBase.generated.h"

UCLASS()
class OMOK_API AOmokGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	DECLARE_DELEGATE_OneParam(
		FOnUpdatedServerTimeSeconds,
		const float /*ServerTimeSeconds*/
	);

	DECLARE_DELEGATE_ThreeParams(
		FOnShiftedCurrentPlayerColor,
		const uint8 /*CurrentPlayerColor*/,
		const float /*ServerTimeSeconds*/,
		const float /*PlayerTime*/
	);

public:
	AOmokGameStateBase();
	
	//전달받은 메세지를 송신자 제외한 나머지 플레이어 스테이트에 배분하는 함수. 서버 전용.
	void DistributeMessage(const FText& InText, const TObjectPtr<class AOmokPlayerState> Sender);

	//플레이어가 놓은 바둑알 위치를 나머지 플레이어 스테이트에 배분하는 함수. 서버 전용.
	void DistributeNodeCoord(const FIntVector2& InCoord, const TObjectPtr<class AOmokPlayerState> Sender);

	void RequestMatchEnd(const TObjectPtr<class AOmokPlayerState> Surrenderer);


public:
	virtual void HandleBeginPlay() override;

	virtual void UpdateServerTimeSeconds() override;

	virtual void OnRep_ReplicatedWorldTimeSeconds() override;



public:
	FORCEINLINE const uint8 GetCurrentPlayerColor() const { return CurrentPlayerColor; }



protected:
	//플레이 시간으로 전환. 서버 전용.
	void ShiftToPlay();

	//휴식 시간으로 전환. 서버 전용.
	void ShiftToRest();

	UFUNCTION()
	void OnRep_CurrentPlayerColor();

	void FinishMatch();


protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



public:
	const float PlayTime = 10.f;	//턴당 플레이 시간.
	const float RestTime = 3.f;		//턴당 휴식 시간.
	FOnUpdatedServerTimeSeconds OnUpdateServerTimeSeconds;
	FOnShiftedCurrentPlayerColor OnShiftedCurrentPlayerColor;



private:
	//현재 플레이중인 플레이어 색상. 0: 검은색, 1: 흰색, 2: 누구 차례도 아님.
	UPROPERTY(ReplicatedUsing = OnRep_CurrentPlayerColor)
	uint8 CurrentPlayerColor;	
		
	//이전 플레이했던 플레이어 색상. 0: 검은색, 1: 흰색.
	uint8 PrevPlayerColor;		

	FTimerDelegate PlayTimerDelegate;	//ShiftToPlay 함수 연결 델리게이트.
	FTimerDelegate RestTimerDelegate;	//ShiftToRest 함수 연결 델리게이트.

	FTimerHandle GameStateTimerHandle;



};
