// Copyright Epic Games, Inc. All Rights Reserved.


#include "OmokGameModeBase.h"
#include "OmokGameStateBase.h"
#include "Player/OmokPlayer.h"
#include "Player/OmokPlayerState.h"
#include "Player/OmokPlayerController.h"
#include "Engine/Engine.h"
#include "Omok.h"
#include "GameDelegates.h"
#include "GameFramework/GameState.h"

AOmokGameModeBase::AOmokGameModeBase()
{
	DefaultPawnClass = AOmokPlayer::StaticClass();
	PlayerControllerClass = AOmokPlayerController::StaticClass();
	PlayerStateClass = AOmokPlayerState::StaticClass();
	GameStateClass = AOmokGameStateBase::StaticClass();
	
	bServerReady = false;
	bClientReady = false;
	bWhite = FMath::RandBool();
}

APlayerController* AOmokGameModeBase::Login(
	UPlayer* NewPlayer,
	ENetRole InRemoteRole,
	const FString& Portal,
	const FString& Options,
	const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage
)
{
	APlayerController* NewPC = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	//세번째 플레이어는 받지 않는다.
	if(2 < GetWorld()->GetNumPlayerControllers())
	{
		ErrorMessage = TEXT("The third Player is not acceptable for this game.");
		return nullptr;
	}

	return NewPC;
}

void AOmokGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(TEXT("PlayLevel") != GetWorld()->GetName())
	{
		return;
	}

	//플레이어별 색상 배정.
	CastChecked<AOmokPlayerController>(NewPlayer)->GetPlayerState<AOmokPlayerState>()->SetbWhite(bWhite);
	bWhite = !bWhite;
}

void AOmokGameModeBase::SetServerReady(TObjectPtr<AOmokPlayerController> ThisOmokPC)
{
	if(bServerReady)
	{
		return;
	}

	bServerReady = true;

	if(bServerReady && bClientReady)
	{
		ensure(CanServerTravel(TEXT("/Game/Maps/PlayLevel?Listen"), true));
		GetWorld()->NextTravelType = ETravelType::TRAVEL_Absolute;
		ProcessServerTravel(TEXT("/Game/Maps/PlayLevel?Listen"), true);
	}
	else
	{
		for(FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++)
		{
			if(it->Get() == ThisOmokPC)
			{
				continue;
			}

			//클라이언트의 Ready 버튼을 깜빡거리게 한다.
			CastChecked<AOmokPlayerController>(it->Get())->ClientRPC_FlickerReadyButton();
		}
	}
}

void AOmokGameModeBase::SetClientReady(TObjectPtr<AOmokPlayerController> ThisOmokPC)
{
	if(bClientReady)
	{
		return;
	}

	bClientReady = true;

	if(bServerReady && bClientReady)
	{
		ensure(CanServerTravel(TEXT("/Game/Maps/PlayLevel?Listen"), true));
		GetWorld()->NextTravelType = ETravelType::TRAVEL_Absolute;
		ProcessServerTravel(TEXT("/Game/Maps/PlayLevel?Listen"), true);
	}
	else
	{
		for(FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++)
		{
			if(it->Get() == ThisOmokPC)
			{
				continue;
			}

			//서버의 Ready 버튼을 깜빡거리게 한다.
			CastChecked<AOmokPlayerController>(it->Get())->FlickerReadyButton();
		}
	}
}
