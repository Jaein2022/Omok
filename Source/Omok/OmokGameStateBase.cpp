// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokGameStateBase.h"
#include "OmokGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Player/OmokPlayerState.h"
#include "Omok.h"

AOmokGameStateBase::AOmokGameStateBase()
{
	bReplicates = true;

	if(false == HasAuthority())
	{
		return;
	}

	CurrentPlayerColor = 2;
	PlayTimerDelegate.BindUObject(this, &AOmokGameStateBase::ShiftToPlay);
	RestTimerDelegate.BindUObject(this, &AOmokGameStateBase::ShiftToRest);
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

void AOmokGameStateBase::DistributeNodeCoord(const FIntVector2& InCoord, const TObjectPtr<AOmokPlayerState> Sender)
{
	ensure(HasAuthority());

	TObjectPtr<AOmokPlayerState> ServerPlayerState = nullptr;

	for(TObjectPtr<APlayerState> PS : PlayerArray)
	{
		//서버 플레이어의 플레이어 스테이트만 분리한다.
		if(PS->GetPawn()->IsLocallyControlled())
		{
			ServerPlayerState = CastChecked<AOmokPlayerState>(PS);
		}

		if(PS == Sender)
		{
			continue;
		}
		
		CastChecked<AOmokPlayerState>(PS)->ClientRPC_DeliverNodeCoord(InCoord, Sender->GetbWhite());
	}

	//서버에서 승리 조건을 달성했는지 판별한다.
	if(ServerPlayerState->IsWinner(InCoord, Sender->GetbWhite()))
	{
		FinishMatch();
		GetWorld()->GetAuthGameMode<AOmokGameModeBase>()->BroadcastMatchEnd(Sender->GetPlayerController());
	}
	else
	{
		ShiftToRest();
	}
}

void AOmokGameStateBase::RequestMatchEnd(const TObjectPtr<class AOmokPlayerState> Surrenderer)
{
	FinishMatch();

	for(TObjectPtr<APlayerState> PS : PlayerArray)
	{
		if(PS == Surrenderer)
		{
			continue;
		}

		GetWorld()->GetAuthGameMode<AOmokGameModeBase>()->BroadcastMatchEnd(PS->GetPlayerController());
	}
}

void AOmokGameStateBase::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	if(false == HasAuthority())
	{
		return;
	}

	if(TEXT("PlayLevel") != GetWorld()->GetName())
	{
		return;
	}
	
	PrevPlayerColor = FMath::RandBool();
	GetWorldTimerManager().SetTimer(GameStateTimerHandle, PlayTimerDelegate, RestTime, false);
}

void AOmokGameStateBase::UpdateServerTimeSeconds()
{
	Super::UpdateServerTimeSeconds();
	OnUpdateServerTimeSeconds.ExecuteIfBound(GetServerWorldTimeSeconds());
}

void AOmokGameStateBase::OnRep_ReplicatedWorldTimeSeconds()
{
	Super::OnRep_ReplicatedWorldTimeSeconds();
	OnUpdateServerTimeSeconds.ExecuteIfBound(GetServerWorldTimeSeconds());
}

void AOmokGameStateBase::ShiftToPlay()
{
	ensure(HasAuthority());
	ensure(2 > PrevPlayerColor);

	CurrentPlayerColor = PrevPlayerColor == 1 ? 0 : 1;	//이전 색상의 반대색으로 설정.
	OnShiftedCurrentPlayerColor.ExecuteIfBound(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);
	PrevPlayerColor = CurrentPlayerColor;

	GetWorldTimerManager().ClearTimer(GameStateTimerHandle);
	GetWorldTimerManager().SetTimer(GameStateTimerHandle, RestTimerDelegate, PlayTime, false);
}

void AOmokGameStateBase::ShiftToRest()
{
	ensure(HasAuthority());

	CurrentPlayerColor = 2;
	OnShiftedCurrentPlayerColor.ExecuteIfBound(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);

	GetWorldTimerManager().ClearTimer(GameStateTimerHandle);
	GetWorldTimerManager().SetTimer(GameStateTimerHandle, PlayTimerDelegate, RestTime, false);
}

void AOmokGameStateBase::OnRep_CurrentPlayerColor()
{
	OnShiftedCurrentPlayerColor.ExecuteIfBound(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);
}

void AOmokGameStateBase::FinishMatch()
{
	ensure(HasAuthority());

	CurrentPlayerColor = 2;
	OnShiftedCurrentPlayerColor.ExecuteIfBound(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);

	GetWorldTimerManager().ClearTimer(GameStateTimerHandle);
}

void AOmokGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AOmokGameStateBase, CurrentPlayerColor);
}