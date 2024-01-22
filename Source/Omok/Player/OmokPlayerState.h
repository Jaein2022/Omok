// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OmokPlayerState.generated.h"

//채팅 메세지, 놓은 바둑돌 좌표 전송 담당 클래스.
UCLASS()
class OMOK_API AOmokPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AOmokPlayerState();

	UFUNCTION(Server, Unreliable)
	void ServerRPC_DeliverMessage(const FText& InText);

	UFUNCTION(Client, Unreliable)
	void ClientRPC_DeliverMessage(const FText& InText, const uint8 SenderColor);

	UFUNCTION(Server, Reliable)
	void ServerRPC_DeliverNodeCoord(const FIntVector2& InCoord);

	UFUNCTION(Client, Reliable)
	void ClientRPC_DeliverNodeCoord(const FIntVector2& InCoord, const uint8 SenderColor);

	//InbWhite 색상의 플레이어가 이겼는지 확인하는 함수. 서버 전용.
	bool IsWinner(const FIntVector2& InCoord, const uint8 InbWhite) const;

	//해당 플레이어 턴이면 true 반환. 
	bool IsMyTurn() const;


public:
	FORCEINLINE void SetbWhite(const uint8 InbWhite) { bWhite = InbWhite; }
	FORCEINLINE const uint8 GetbWhite() const { return bWhite; }


protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_bWhite();



private:
	UPROPERTY(ReplicatedUsing = OnRep_bWhite)
	uint8 bWhite : 1;

};
