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
#include "Omok/OmokGameStateBase.h"
#include "Omok/Omok.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AOmokPlayerController::AOmokPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	PrimaryActorTick.bCanEverTick = true;

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

void AOmokPlayerController::ReceiveMessage(const FText& InText, const uint8 SenderColor)
{
	PlayUI->DisplayReceivedMessage(InText, SenderColor);
}

void AOmokPlayerController::SetMessageColor(const uint8 InbWhite)
{
	PlayUI->SetOwningPlayerColor(InbWhite);
}

void AOmokPlayerController::ClientRPC_DisplayResult_Implementation(const uint8 WinnerColor)
{
	FOmokDevelopmentSupport::DisplayDebugMessageForActors(this, __FUNCTION__, TEXT("Result."), 30.f);

	PlayUI->DisplayResult(WinnerColor);
}

void AOmokPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//서버가 가진 클라이언트의 플레이어 컨트롤러는 UI를 생성할 필요가 없으므로 생략한다.
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
		HostingUI->GetReadyButton()->OnClicked.AddDynamic(this, &AOmokPlayerController::NotifyOnReadied);
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

		GetWorld()->GetGameState<AOmokGameStateBase>()->OnShiftedCurrentPlayerColor.BindUObject(PlayUI, &UOmokPlayUI::ResetTimer);
		GetWorld()->GetGameState<AOmokGameStateBase>()->OnUpdateServerTimeSeconds.BindUObject(PlayUI, &UOmokPlayUI::UpdateTimerWithServer);
		

		//로컬 컨트롤러이면서 동시에 서버에서 Authority를 가진 플레이어 컨트롤러 == 리슨서버 자신의 플레이어 컨트롤러. 
		//리슨서버의 컨트롤러는 이미 플레이어 스테이트의 생성이 끝나고 PostLogin()을 통해 받은 색상을 가져오므로 문제 없지만, 
		// 클라이언트는 로컬 플레이어 컨트롤러의 BeginPlay() 이후 PostLogin()까지 거친 후에 프록시 플레이어 스테이트가 생성되므로 
		// 이 시점에서 플레이어 스테이트를 호출하면 널포인터가 반환된다.
		if(HasAuthority())
		{
			PlayUI->SetOwningPlayerColor(GetPlayerState<AOmokPlayerState>()->GetbWhite());
			PlayUI->GetSurrenderButton()->OnClicked.AddDynamic(GetPlayerState<AOmokPlayerState>(), &AOmokPlayerState::ServerRPC_Surrender);
		}
	}
}

void AOmokPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(nullptr == PlayUI)
	{
		return;
	}

	PlayUI->UpdateTimerWithLocalDeltaTime(DeltaSeconds);
}

void AOmokPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AOmokPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(GetWorld()->GetName() != TEXT("PlayLevel"))
	{
		return;
	}

	UInputMappingContext* IMC = LoadObject<UInputMappingContext>(
		NULL,
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Player/Input/IMC_OmokPlayerController.IMC_OmokPlayerController'")
	);
	ensure(IMC);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(IMC, 0);

	UInputAction* IA = LoadObject<UInputAction>(
		NULL,
		TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/IA_OmokRightClick.IA_OmokRightClick'")
	);
	ensure(IA);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(IA, ETriggerEvent::Triggered, this, &AOmokPlayerController::OnMouseRightClicked);
}

void AOmokPlayerController::OnRep_PlayerState()
{
	if(TEXT("PlayLevel") != GetWorld()->GetName())
	{
		return;
	}

	PlayUI->GetSurrenderButton()->OnClicked.AddDynamic(GetPlayerState<AOmokPlayerState>(), &AOmokPlayerState::ServerRPC_Surrender);
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

void AOmokPlayerController::NotifyOnReadied()
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

	GetPlayerState<AOmokPlayerState>()->ServerRPC_DeliverMessage(InText);
}

void AOmokPlayerController::OnClickedSendButton_SendMessage()
{
	const FText Message = PlayUI->GetMessageInputbox()->GetText();
	GetPlayerState<AOmokPlayerState>()->ServerRPC_DeliverMessage(Message);
}

void AOmokPlayerController::OnMouseRightClicked()
{
	PlayUI->SwitchMenu();
}
