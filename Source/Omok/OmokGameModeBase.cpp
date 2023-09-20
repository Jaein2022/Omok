// Copyright Epic Games, Inc. All Rights Reserved.


#include "OmokGameModeBase.h"
#include "OmokPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AOmokGameModeBase::AOmokGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> OmokPlayerClassRef
	(
		TEXT("/Script/CoreUObject.Class'/Script/Omok.OmokPlayer'")
	);
	ensure(OmokPlayerClassRef.Succeeded());
	this->DefaultPawnClass = OmokPlayerClassRef.Class;

	static ConstructorHelpers::FClassFinder<AOmokPlayerController> OmokPlayerControllerClassRef
	(
		TEXT("/Script/CoreUObject.Class'/Script/Omok.OmokPlayerController'")
	);
	ensure(OmokPlayerControllerClassRef.Succeeded());
	this->PlayerControllerClass = OmokPlayerControllerClassRef.Class;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObjectRef(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Player/Input/IMC_OmokPlayer.IMC_OmokPlayer'")
	);
	ensure(IMCObjectRef.Succeeded());
	this->IMC = IMCObjectRef.Object;



}

void AOmokGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AOmokGameModeBase::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AOmokGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(this->IMC, 0);
}
