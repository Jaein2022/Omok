// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayerState.h"
#include "OmokPlayerController.h"
#include "Omok/OmokGameStateBase.h"
#include "Omok/Omok.h"

AOmokPlayerState::AOmokPlayerState()
{
	bReplicates = true;
}

const uint8 AOmokPlayerState::GetbWhite() const
{
	return CastChecked<AOmokPlayerController>(GetOwningController())->GetbWhite();
}

void AOmokPlayerState::ServerRPC_DeliverMessage_Implementation(const FText& InText)
{
	GetWorld()->GetGameState<AOmokGameStateBase>()->DistributeMessage(InText, this);
}

void AOmokPlayerState::ClientRPC_DeliverMessage_Implementation(const FText& InText, const uint8 SenderColor)
{
	CastChecked<AOmokPlayerController>(GetOwningController())->ReceiveMessage(InText, SenderColor);
}