// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"



UOmokGameInstance::UOmokGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UI/UI_Lobby"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	
	MenuClass = MenuBPClass.Class;
}

void UOmokGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}



void UOmokGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	
	Menu->Setup();

	Menu->SetMenuInterface(this);

}

void UOmokGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/TestMap?listen");

}

void UOmokGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);


}