// Copyright Epic Games, Inc. All Rights Reserved.


#include "OmokGameModeBase.h"
#include "Player/OmokPlayerController.h"
#include "OmokGameStateBase.h"
#include "Player/OmokPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Board/OmokBoard.h"

AOmokGameModeBase::AOmokGameModeBase()
{
	DefaultPawnClass = AOmokPlayer::StaticClass();
	PlayerControllerClass = AOmokPlayerController::StaticClass();
	GameStateClass = AOmokGameStateBase::StaticClass();
}

void AOmokGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(ENetMode::NM_Standalone == NewPlayer->GetNetMode())
	{
		return;
	}

	AOmokPlayerController* NewOmokPLayer = CastChecked<AOmokPlayerController>(NewPlayer);

}

void AOmokGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AOmokGameModeBase::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

