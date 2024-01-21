// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Player/OmokPlayerState.h"

AOmokGameStateBase::AOmokGameStateBase()
{
	bReplicates = true;
}

void AOmokGameStateBase::DistributeMessage(const FText& InText, const TObjectPtr<AOmokPlayerState> Sender)
{	
	ensure(HasAuthority());

	for(TObjectPtr<APlayerState> PS : PlayerArray)
	{
		if(PS == Sender)
		{
			continue;
		}

		CastChecked<AOmokPlayerState>(PS)->ClientRPC_DeliverMessage(InText, Sender->GetbWhite());
	}
}

void AOmokGameStateBase::DistributeNodeCoord(const FIntVector2& InCoord, const TObjectPtr<class AOmokPlayerState> Sender)
{
	ensure(HasAuthority());

	for(TObjectPtr<APlayerState> PS : PlayerArray)
	{
		if(PS == Sender)
		{
			continue;
		}

		CastChecked<AOmokPlayerState>(PS)->ClientRPC_DeliverNodeCoord(InCoord, Sender->GetbWhite());
	}
}

void AOmokGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
