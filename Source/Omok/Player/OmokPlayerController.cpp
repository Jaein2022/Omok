// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "../UI/OmokLobbyUI.h"
#include "../UI/OmokHostingUI.h"
#include "Kismet/GameplayStatics.h"

AOmokPlayerController::AOmokPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	bWhite = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> LobbyUIClassRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_OmokLobbyUI.WBP_OmokLobbyUI_C'")
	);
	ensure(LobbyUIClassRef.Succeeded());
	LobbyUIClass = LobbyUIClassRef.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> HostingUIClassRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_OmokHostingUI.WBP_OmokHostingUI_C'")
	);
	ensure(HostingUIClassRef.Succeeded());
	HostingUIClass = HostingUIClassRef.Class;
}

void AOmokPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(false == IsLocalController())
	{
		return;
	}

	LobbyUI = CastChecked<UOmokLobbyUI>(CreateWidget(this, LobbyUIClass));
	LobbyUI->AddToViewport();
	HostingUI = CastChecked<UOmokHostingUI>(CreateWidget(this, HostingUIClass));
	HostingUI->AddToViewport();

	const FString CurrentWorldName = GetWorld()->GetName();
	if(CurrentWorldName == TEXT("Lobby"))
	{
		HostingUI->SetVisibility(ESlateVisibility::Hidden);
		HostingUI->SetIsEnabled(false);

		LobbyUI->SetIsEnabled(true);
		LobbyUI->SetVisibility(ESlateVisibility::Visible);
	}
	else if(CurrentWorldName == TEXT("HostingLevel"))
	{
		LobbyUI->SetVisibility(ESlateVisibility::Hidden);
		LobbyUI->SetIsEnabled(false);

		HostingUI->SetIsEnabled(true);
		HostingUI->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void AOmokPlayerController::StartHosting() const
{
	ensure(GetWorld()->ServerTravel(TEXT("/Game/Maps/HostingLevel?Listen")));
}

void AOmokPlayerController::CancelHosting() 
{
	ClientTravel(TEXT("/Game/Maps/Lobby"), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::ConnectToIPAddress(const FText& IPAddress)
{
	ClientTravel(IPAddress.ToString(), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::Disconnect()
{
	ClientTravel(TEXT("/Game/Maps/Lobby"), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::QuitGame()
{
	ConsoleCommand("quit");
}
