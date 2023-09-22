﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


bool UMainMenu::Initialize()
{

	bool Success = Super::Initialize();
	if (!Success) return false;

	// TODO: setup

	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(Enter != nullptr)) return false;
	Enter->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(Back != nullptr)) return false;
	Back->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	return true;

}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterfaceP)
{
	this->MenuInterface = MenuInterfaceP;
}

void UMainMenu::Setup()
{

	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;

}



void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a Server!"));
}

void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna Join a Server!"));
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(SubMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(SubMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}
