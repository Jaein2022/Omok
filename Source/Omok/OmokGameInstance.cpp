// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"



UOmokGameInstance::UOmokGameInstance(const FObjectInitializer& ObjectInitializer)
{
	//ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UI/UI_Lobby"));
	//if (!ensure(MenuBPClass.Class != nullptr)) return;
	//
	//MenuClass = MenuBPClass.Class;
	//
	//ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/UI/UI_InGameMenu"));
	//if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	//InGameMenuClass = InGameMenuBPClass.Class;
}

void UOmokGameInstance::Init()
{
	Super::Init();

	//UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *InGameMenuClass->GetName());
}

//void UOmokGameInstance::LoadMenu()
//{
//
//	if (!ensure(MenuClass != nullptr)) return;
//	
//	Menu = CreateWidget<UMainMenu>(this, MenuClass);
//	if (!ensure(Menu != nullptr)) return;
//	
//	Menu->Setup();
//
//	Menu->SetMenuInterface(this);
//
//}
//
//void UOmokGameInstance::InGameLoadMenu()
//{
//
//	if (!ensure(InGameMenuClass != nullptr)) return;
//
//	InMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
//	if (!ensure(InMenu != nullptr)) return;
//
//	InMenu->Setup();
//
//	InMenu->SetMenuInterface(this);
//
//}
//
//void UOmokGameInstance::Host()
//{
//	if (Menu != nullptr) 
//	{
//		Menu->Teardown();
//	}
//
//	UEngine* Engine = GetEngine();
//	if (!ensure(Engine != nullptr)) return;
//
//	Engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting"));
//
//	UWorld* World = GetWorld();
//	if (!ensure(World != nullptr)) return;
//
//	//World->ServerTravel("/Game/Maps/TestMap?listen");
//	World->ServerTravel("/Game/Maps/PlayMap?listen");
//	
//}
//
//void UOmokGameInstance::Join(const FString& Address)
//{
//	if (Menu != nullptr) 
//	{
//		Menu->Teardown();
//	}
//
//	UEngine* Engine = GetEngine();
//	if (!ensure(Engine != nullptr)) return;
//
//	Engine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Joining %s"), *Address));
//
//	APlayerController* PlayerController = GetFirstLocalPlayerController();
//	if (!ensure(PlayerController != nullptr)) return;
//
//	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
//
//}
//
//void UOmokGameInstance::LoadMainMenu()
//{
//
//	APlayerController* PlayerController = GetFirstLocalPlayerController();
//	if (!ensure(PlayerController != nullptr)) return;
//
//	PlayerController->ClientTravel("/Game/Maps/Lobby", ETravelType::TRAVEL_Absolute);
//
//
//}

void UOmokGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	OnWorldChangedDelegate.Broadcast(OldWorld, NewWorld);
}
