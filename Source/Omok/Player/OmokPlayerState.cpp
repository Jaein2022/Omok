// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayerState.h"
#include "OmokPlayerController.h"
#include "Omok/OmokGameStateBase.h"
#include "Omok/Omok.h"
#include "Net/UnrealNetwork.h"

AOmokPlayerState::AOmokPlayerState()
{
	bReplicates = true;
}

void AOmokPlayerState::ServerRPC_DeliverMessage_Implementation(const FText& InText)
{
	GetWorld()->GetGameState<AOmokGameStateBase>()->DistributeMessage(InText, this);
}

void AOmokPlayerState::ClientRPC_DeliverMessage_Implementation(const FText& InText, const uint8 SenderColor)
{
	CastChecked<AOmokPlayerController>(GetOwningController())->ReceiveMessage(InText, SenderColor);
}

void AOmokPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AOmokPlayerState, bWhite, COND_InitialOnly);
}

void AOmokPlayerState::OnRep_bWhite()
{
	//유저의 로컬 플레이어 컨트롤러를 제외한 나머지 플레이어의 컨트롤러는 프록시가 존재하지 않으므로 
	// 프록시 플레이어 스테이트가 플레이어 컨트롤러를 호출하면 로컬 소속 제외한 나머지는 널포인터가 반환된다.
	if(GetOwningController())
	{
		CastChecked<AOmokPlayerController>(GetOwningController())->SetMessageColor(bWhite);
	}
}