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
		GetWorld()->GetAuthGameMode<AOmokGameModeBase>()->BroadcastWinner(Sender->GetPlayerController());
		//
	}
	else
	{
		ShiftToRest();
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

	FOmokDevelopmentSupport::DisplayDebugMessageForActors(
		this,
		__FUNCTION__,
		TEXT("Shifting Test"),
		30.f,
		CurrentPlayerColor == 2 ? FColor::Red : FColor::Blue
	);
	
	PrevPlayerColor = FMath::RandBool();
	GetWorldTimerManager().SetTimer(GameStateTimerHandle, PlayTimerDelegate, RestTime, false);
}

void AOmokGameStateBase::UpdateServerTimeSeconds()
{
	Super::UpdateServerTimeSeconds();
	OnUpdateServerWorldTimeSeconds.Broadcast(GetServerWorldTimeSeconds());
}

void AOmokGameStateBase::OnRep_ReplicatedWorldTimeSeconds()
{
	Super::OnRep_ReplicatedWorldTimeSeconds();
	OnUpdateServerWorldTimeSeconds.Broadcast(GetServerWorldTimeSeconds());
}

void AOmokGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AOmokGameStateBase, CurrentPlayerColor);
}

void AOmokGameStateBase::ShiftToPlay()
{
	ensure(HasAuthority());

	CurrentPlayerColor = PrevPlayerColor == 1 ? 0 : 1;	//이전 색상의 반대색으로 설정.
	OnShiftedCurrentPlayerColor.Broadcast(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);
	PrevPlayerColor = CurrentPlayerColor;

	FOmokDevelopmentSupport::DisplayDebugMessageForActors(
		this,
		__FUNCTION__,
		TEXT("Shifting Test"),
		30.f,
		CurrentPlayerColor ? FColor::White : FColor::Black
	);

	GetWorldTimerManager().ClearTimer(GameStateTimerHandle);
	GetWorldTimerManager().SetTimer(GameStateTimerHandle, RestTimerDelegate, PlayTime, false);
}

void AOmokGameStateBase::ShiftToRest()
{
	ensure(HasAuthority());

	CurrentPlayerColor = 2;
	OnShiftedCurrentPlayerColor.Broadcast(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);

	FOmokDevelopmentSupport::DisplayDebugMessageForActors(
		this,
		__FUNCTION__,
		TEXT("Shifting Test"),
		30.f
	);

	GetWorldTimerManager().ClearTimer(GameStateTimerHandle);
	GetWorldTimerManager().SetTimer(GameStateTimerHandle, PlayTimerDelegate, RestTime, false);
}

void AOmokGameStateBase::OnRep_CurrentPlayerColor()
{
	OnShiftedCurrentPlayerColor.Broadcast(CurrentPlayerColor, GetServerWorldTimeSeconds(), PlayTime);
}
