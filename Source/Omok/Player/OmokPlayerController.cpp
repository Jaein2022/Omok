// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayerController.h"
#include "Omok/UI/OmokLobbyUI.h"
#include "Omok/UI/OmokHostingUI.h"
#include "Components/Button.h"
#include "Omok/OmokGameModeBase.h"

AOmokPlayerController::AOmokPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

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

	bReplicates = true;
}

void AOmokPlayerController::ClientRPC_FlickerReadyButton_Implementation()
{
	HostingUI->SetFlickeringOn();
}

void AOmokPlayerController::FlickerReadyButton()
{
	HostingUI->SetFlickeringOn();
}

void AOmokPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(false == IsLocalController())
	{
		return;
	}
	
	//GEngine->OnNetworkFailure().AddUObject(this, &AOmokPlayerController::NetworkFailureTestFunc);

	const FString CurrentWorldName = GetWorld()->GetName();
	if(CurrentWorldName == TEXT("Lobby"))
	{
		LobbyUI = CastChecked<UOmokLobbyUI>(CreateWidget(this, LobbyUIClass));
		LobbyUI->GetHostButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::StartHosting);
		LobbyUI->GetQuitButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::QuitGame);
		LobbyUI->GetEnterButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::ConnectToIPAddress);
		LobbyUI->GetBackButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::Disconnect);
		LobbyUI->AddToViewport();
	}
	else if(CurrentWorldName == TEXT("HostingLevel"))
	{
		HostingUI = CastChecked<UOmokHostingUI>(CreateWidget(this, HostingUIClass));
		HostingUI->GetReadyButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::OnClickedReadyButton);
		HostingUI->GetCancelButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::CancelHosting);
		HostingUI->AddToViewport();
		HostingUI->SetWaiting();
		
		if(ENetMode::NM_Client == GetWorld()->GetNetMode())
		{
			//접속한 클라이언트는 대기할 필요 없이 바로 Ready버튼을 누를 수 있게 한다.
			HostingUI->SetJoined();

			//클라이언트가 접속 취소할 때 LobbyUI에서 JoinMenu를 보여주게 한다.
			UOmokLobbyUI::SwitchToJoinMenu();
		}
	}
	else if(CurrentWorldName == TEXT("PlayLevel"))
	{


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

void AOmokPlayerController::OnClickedReadyButton()
{
	if(HasAuthority())
	{
		GetWorld()->GetAuthGameMode<AOmokGameModeBase>()->SetServerReady(this);
	}
	else
	{
		ServerRPC_NotifyOnReadied();
	}
}

void AOmokPlayerController::QuitGame()
{
	ConsoleCommand("quit");
}

void AOmokPlayerController::ServerRPC_NotifyOnReadied_Implementation()
{
	GetWorld()->GetAuthGameMode<AOmokGameModeBase>()->SetClientReady(this);
}