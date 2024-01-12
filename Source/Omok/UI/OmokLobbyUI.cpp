// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokLobbyUI.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "../Player/OmokPlayerController.h"

UOmokLobbyUI::UOmokLobbyUI(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{	
}

void UOmokLobbyUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	OwningPlayerController = CastChecked<AOmokPlayerController>(GetOwningPlayer());

	ensure(MenuSwitcher);

	ensure(MainMenu);

	ensure(HostButton);
	HostButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedHostButton);

	ensure(JoinButton);
	JoinButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedJoinButton);

	ensure(QuitButton);
	QuitButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedQuitButton);

	
	
	ensure(JoinMenu);

	ensure(IPAddress);

	ensure(EnterButton);
	EnterButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedEnterButton);

	ensure(BackButton);
	BackButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedBackButton);

	
	
	//ensure(ReadyMenu);

	//ensure(ReadyButton);
	//ReadyButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedReadyButton);

	//ensure(ReadyButtonTextBlock);

	//FTextFlickeringTimerDelegate.BindUFunction(
	//	this,
	//	GET_FUNCTION_NAME_CHECKED(UOmokLobbyUI, FlickerReadyButtonText)
	//);

	//TextFlickeringTimerHandle.Invalidate();

	//bFlickeringSwitch = true;

	//ensure(CancelButton);
	//CancelButton->OnClicked.AddDynamic(this, &UOmokLobbyUI::OnClickedCancelButton);

	
}

void UOmokLobbyUI::OnClickedHostButton()
{
	OwningPlayerController->StartHosting();
}

void UOmokLobbyUI::OnClickedJoinButton()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UOmokLobbyUI::OnClickedQuitButton() 
{
	OwningPlayerController->QuitGame();
}

void UOmokLobbyUI::OnClickedEnterButton()
{
	if(IPAddress->GetText().IsEmpty())
	{
		ensureMsgf(false, TEXT("%s"), TEXT("IP address must not be empty."));
		return;
	}

	OwningPlayerController->ConnectToIPAddress(IPAddress->GetText());
}

void UOmokLobbyUI::OnClickedBackButton()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}

//void UOmokLobbyUI::OnClickedReadyButton()
//{
//}
//
//void UOmokLobbyUI::FlickerReadyButtonText()
//{
//	ReadyButtonTextBlock->SetOpacity(bFlickeringSwitch ? 1.f : 0.f);
//	bFlickeringSwitch = bFlickeringSwitch ? false : true;
//}
//
//void UOmokLobbyUI::OnClickedCancelButton()
//{
//	TextFlickeringTimerHandle.Invalidate();
//	MenuSwitcher->SetActiveWidget(JoinMenu);
//}
