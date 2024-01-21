// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OmokPlayerState.generated.h"

//
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
