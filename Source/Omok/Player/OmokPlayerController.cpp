// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayerController.h"
#include "../UI/OmokLobbyUI.h"
#include "../UI/OmokHostingUI.h"
#include "Components/Button.h"

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
	LobbyUI->GetHostButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::StartHosting);
	LobbyUI->GetQuitButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::QuitGame);
	LobbyUI->GetEnterButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::ConnectToIPAddress);
	LobbyUI->GetBackButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::Disconnect);
	LobbyUI->AddToViewport();

	HostingUI = CastChecked<UOmokHostingUI>(CreateWidget(this, HostingUIClass));
	HostingUI->GetCancelButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::CancelHosting);
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
		
		if(ENetMode::NM_Client == GetWorld()->GetNetMode())
		{
			//접속한 클라이언트는 대기할 필요 없이 바로 Ready버튼 누를 수 있게 한다.
			HostingUI->SetJoined();
		}
	}
}

void AOmokPlayerController::StartHosting()
{
	ensure(GetWorld()->ServerTravel(TEXT("/Game/Maps/HostingLevel?Listen"), true));
}

void AOmokPlayerController::CancelHosting() 
{
	ClientTravel(TEXT("/Game/Maps/Lobby"), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::ConnectToIPAddress()
{
	const FString IPAddress = LobbyUI->GetIPAddress();
	ensureMsgf(false == IPAddress.IsEmpty(), TEXT("%s"), TEXT("IP address must not be empty."));
	
	ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::Disconnect()
{
	ClientTravel(TEXT("/Game/Maps/Lobby?closed"), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::QuitGame()
{
	ConsoleCommand("quit");
}
