// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokLobbyUI.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

bool UOmokLobbyUI::bRetunedFromHost = false;

UOmokLobbyUI::UOmokLobbyUI(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{	
}

void UOmokLobbyUI::SetIsEnabled(bool bInIsEnabled)
{
	Super::SetIsEnabled(bInIsEnabled);

	if(false == bInIsEnabled)
	{
		return;
	}

	if(bRetunedFromHost)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
		bRetunedFromHost = false;
	}
}

const FString& UOmokLobbyUI::GetIPAddress() const
{
	return IPAddressBox->GetText().ToString();
}

void UOmokLobbyUI::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(MenuSwitcher);

	ensure(MainMenu);

	ensure(HostButton);

	ensure(JoinButton);
	JoinButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedJoinButton);

	ensure(QuitButton);

	
	
	ensure(JoinMenu);

	ensure(IPAddressBox);

	ensure(EnterButton);

	ensure(BackButton);
	BackButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedBackButton);


	if(ENetMode::NM_Client == GetWorld()->GetNetMode())
	{
		bRetunedFromHost = true;
	}

	//GetGameInstance()->OnNotifyPreClientTravel().AddUObject(this, &UOmokLobbyUI::OnDisconnected);
	//GEngine->OnNetworkFailure().AddUObject(this, &UOmokLobbyUI::OnFailedToJoin);
	//FGameDelegates::Get().GetHandleDisconnectDelegate().AddUObject(this, &UOmokLobbyUI::OnFailedToJoin);


	
}

void UOmokLobbyUI::OnClickedJoinButton()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UOmokLobbyUI::OnClickedBackButton()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}

//void UOmokLobbyUI::OnFailedToJoin(class UWorld* World, class UNetDriver* NetDriver)
//{
//	int32 temp = 0;
//}

//void UOmokLobbyUI::FlickerReadyButtonText()
//{
//	ReadyButtonTextBlock->SetOpacity(bFlickeringSwitch ? 1.f : 0.f);
//	bFlickeringSwitch = bFlickeringSwitch ? false : true;
//}
