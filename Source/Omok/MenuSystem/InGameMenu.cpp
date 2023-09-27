// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

bool UInGameMenu::Initialize()
{

	bool Success = Super::Initialize();
	if (!Success) return false;

	// TODO: setup

	if (!ensure(Surrender != nullptr)) return false;
	Surrender->OnClicked.AddDynamic(this, &UInGameMenu::ExitServer);


	return true;
}

void UInGameMenu::ExitServer()
{
	if (MenuInterface != nullptr) {
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

