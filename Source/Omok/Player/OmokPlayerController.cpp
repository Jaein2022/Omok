// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayerController.h"
#include "OmokPlayerState.h"
#include "OmokPlayer.h"
#include "Omok/UI/OmokLobbyUI.h"
#include "Omok/UI/OmokHostingUI.h"
#include "Omok/UI/OmokPlayUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Omok/OmokGameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameState.h"
#include "Omok/Omok.h"
#include "Net/UnrealNetwork.h"

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

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayUIClassRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_OmokPlayUI.WBP_OmokPlayUI_C'")
	);
	ensure(PlayUIClassRef.Succeeded());
	PlayUIClass = PlayUIClassRef.Class;

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

void AOmokPlayerController::ReceiveMessage(const FText& InText, const uint8 SenderColor)
{
	PlayUI->DisplayReceivedMessage(InText, SenderColor);
}

void AOmokPlayerController::SetMessageColor(const uint8 InbWhite)
{
	PlayUI->SetOwningPlayerColor(InbWhite);
}

void AOmokPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(false == IsLocalController())
	{
		return;
	}
	
	//GEngine->OnNetworkFailure().AddUObject(this, &AOmokPlayerController::NetworkFailureTestFunc);

	//auto temp = GetPlayerState<APlayerState>()->GetPlayerName();
	//auto temp1 = GetPlayerState<APlayerState>()->GetUniqueId().GetUniqueNetId()->ToString();
	//auto temp2 = GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId()->ToString();

	const FString CurrentWorldName = GetWorld()->GetName();
	if(CurrentWorldName == TEXT("Lobby"))
	{
		LobbyUI = CastChecked<UOmokLobbyUI>(CreateWidget(this, LobbyUIClass));
		LobbyUI->GetHostButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::StartHosting);
		LobbyUI->GetQuitButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::QuitGame);
		LobbyUI->GetIPAddressBox()->OnTextCommitted.AddDynamic(this, &AOmokPlayerController::OnTextCommitted_Connect);
		LobbyUI->GetEnterButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::OnClickedEnterButton_Connect);
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
		PlayUI = CastChecked<UOmokPlayUI>(CreateWidget(this, PlayUIClass));
		PlayUI->GetMessageInputbox()->OnTextCommitted.AddDynamic(this, &AOmokPlayerController::OnTextCommitted_SendMessage);
		PlayUI->GetSendButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::OnClickedSendButton_SendMessage);
		PlayUI->AddToViewport();

		if(HasAuthority())
		{
			PlayUI->SetOwningPlayerColor(bWhite);
		}
	}
}

void AOmokPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AOmokPlayerController, bWhite, COND_AutonomousOnly);
}

void AOmokPlayerController::StartHosting()
{
	ensure(GetWorld()->ServerTravel(TEXT("/Game/Maps/HostingLevel?Listen"), true));
}

void AOmokPlayerController::CancelHosting() 
{
	ClientTravel(TEXT("/Game/Maps/Lobby?Closed"), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::OnClickedEnterButton_Connect()
{
	const FString IPAddress = LobbyUI->GetIPAddress();
	ensureMsgf(false == IPAddress.IsEmpty(), TEXT("%s"), TEXT("IP address must not be empty."));
	
	ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::OnTextCommitted_Connect(const FText& InText, ETextCommit::Type CommitMethod)
{
	if(ETextCommit::Type::OnEnter != CommitMethod)
	{
		return;
	}

	ensureMsgf(false == InText.IsEmpty(), TEXT("%s"), TEXT("IP address must not be empty."));

	ClientTravel(InText.ToString(), ETravelType::TRAVEL_Absolute);
}

void AOmokPlayerController::Disconnect()
{
	ClientTravel(TEXT("/Game/Maps/Lobby?Closed"), ETravelType::TRAVEL_Absolute);
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

void AOmokPlayerController::OnTextCommitted_SendMessage(const FText& InText, ETextCommit::Type CommitType)
{
	if(ETextCommit::Type::OnEnter != CommitType)
	{
		return;
	}

	GetPlayerState<AOmokPlayerState>();
}

void AOmokPlayerController::OnClickedSendButton_SendMessage()
{
	const FText Message = PlayUI->GetMessageInputbox()->GetText();
	GetPlayerState<AOmokPlayerState>();
}

void AOmokPlayerController::OnRep_bWhite()
{
	PlayUI->SetOwningPlayerColor(bWhite);
}
