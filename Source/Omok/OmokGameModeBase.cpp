// Copyright Epic Games, Inc. All Rights Reserved.


#include "OmokGameModeBase.h"
#include "OmokPlayerController.h"
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

void AOmokGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AOmokGameModeBase::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

//void AOmokGameModeBase::PostLogin(APlayerController* NewPlayer)
//{
//	Super::PostLogin(NewPlayer);
//
//	//ensure(2 >= GetWorld()->GetNumPlayerControllers());
//	
//	//if(true == NewPlayer->IsLocalPlayerController())
//	//{
//	//	NewPlayer->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(this->IMC, 0);
//	//}
//	//일단 안터지게 임시조치.
//
//	//GetWorld()->GetLevels();
//
//	//TObjectPtr<AOmokPlayerController> NewOmokPlayerController = CastChecked<AOmokPlayerController>(NewPlayer);
//	//if(1 < GetWorld()->GetNumPlayerControllers())
//	//{
//	//	NewOmokPlayerController->SetIsWhite(
//	//		!CastChecked<AOmokPlayerController>(GetWorld()->GetFirstPlayerController())->GetIsWhite()
//	//	);
//	//	//두번째 플레이어는 무조건 첫번째 플레이어와 반대 색상을 준다.
//	//}
//	//else
//	//{
//	//	NewOmokPlayerController->SetIsWhite(FMath::RandBool());
//	//	//첫번째 플레이어는 랜덤하게 색상을 골라 준다.
//	//}
//
//
//}
