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

void UOmokLobbyUI::ShowJoinMenu() const
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
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

	if(bRetunedFromHost)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}

	bRetunedFromHost = false;
}

void UOmokLobbyUI::OnClickedJoinButton()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UOmokLobbyUI::OnClickedBackButton()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}
