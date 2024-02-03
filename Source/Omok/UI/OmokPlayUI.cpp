// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Omok/UI/OmokTextBlock.h"
#include "Omok/Omok.h"

void UOmokPlayUI::DisplayReceivedMessage(const FText& InText, const uint8 bColor)
{
	TObjectPtr<UOmokTextBlock> Message = NewObject<UOmokTextBlock>(this);

	Message->SetMessageAndConfig(
		InText,
		MessageScrollBox->GetCachedGeometry().GetLocalSize().X * 0.9f,
		bColor
	);

	MessageScrollBox->AddChild(Message);
	MessageInputBox->SetText(FText());
}

void UOmokPlayUI::ResetTimer(const uint8 InCurrentPlayerColor, const float ServerTimeSeconds, const float PlayTime)
{
	CurrentPlayerColor = InCurrentPlayerColor;
	
	if(2 == CurrentPlayerColor)
	{
		RemainingTime -= ServerTimeSeconds - PrevServerTimeSeconds;
		if(0.f > RemainingTime)
		{
			CurrentRemainingTimeText->SetText(FText::FromString(TEXT("0.00")));
		}
		else
		{
			CurrentRemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), RemainingTime)));
		}
		return;
	}

	RemainingTime = PlayTime;

	CurrentRemainingTimeText->SetColorAndOpacity(FNodeColor::GetAllNodeColors()[CurrentPlayerColor].FixColor);
	CurrentRemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), RemainingTime)));

	PrevServerTimeSeconds = ServerTimeSeconds;
}

void UOmokPlayUI::UpdateTimerWithServer(const float ServerTimeSeconds)
{
	if(2 == CurrentPlayerColor)
	{
		return;
	}

	RemainingTime -= ServerTimeSeconds - PrevServerTimeSeconds;

	if(0.f > RemainingTime)
	{
		CurrentRemainingTimeText->SetText(FText::FromString(TEXT("0.00")));
	}
	else
	{
		CurrentRemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), RemainingTime)));
	}
	
	PrevServerTimeSeconds = ServerTimeSeconds;
}

void UOmokPlayUI::UpdateTimerWithLocalDeltaTime(const float LocalDeltaSeconds)
{
	if(2 == CurrentPlayerColor)
	{
		return;
	}

	RemainingTime -= LocalDeltaSeconds;

	if(0.f > RemainingTime)
	{
		CurrentRemainingTimeText->SetText(FText::FromString(TEXT("0.00")));
	}
	else
	{
		CurrentRemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), RemainingTime)));
	}

	PrevServerTimeSeconds += LocalDeltaSeconds;
}

void UOmokPlayUI::SetOwningPlayerColor(const uint8 InbWhite)
{
	OwningPlayerColor = InbWhite;
	PlayerColorPanel->SetColorAndOpacity(FNodeColor::GetAllNodeColors()[OwningPlayerColor].FixColor);
}

void UOmokPlayUI::SwitchMenu()
{
	if(MenuOverlay->GetIsEnabled())
	{
		MenuOverlay->SetVisibility(ESlateVisibility::Hidden);
		MenuOverlay->SetIsEnabled(false);
	}
	else
	{
		MenuOverlay->SetVisibility(ESlateVisibility::Visible);
		MenuOverlay->SetIsEnabled(true);
	}
}

void UOmokPlayUI::DisplayResult(const uint8 WinnerColor)
{
	MatchEndOverlay->SetVisibility(ESlateVisibility::Visible);
	MatchEndOverlay->SetIsEnabled(true);

	GetWorld()->GetTimerManager().SetTimer(
		TravelingTimerHandle, 
		this,
		&UOmokPlayUI::FlickerTravelingText,
		0.5f,
		true
	);

	WinnerTextBlock->SetColorAndOpacity(FNodeColor::GetAllNodeColors()[WinnerColor].FixColor);

	if(WinnerColor == OwningPlayerColor)
	{
		WinnerTextBlock->SetText(FText::FromString(TEXT("You")));
		ResultTextBlock->SetText(FText::FromString(TEXT("win!")));
	}
	else
	{
		WinnerTextBlock->SetText(FNodeColor::GetAllNodeColors()[WinnerColor].Name);
		ResultTextBlock->SetText(FText::FromString(TEXT("wins")));
	}
}

void UOmokPlayUI::FlickerTravelingText()
{
	if(ESlateVisibility::Visible == TravelingTextBlock->GetVisibility())
	{
		TravelingTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TravelingTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void UOmokPlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(MessageScrollBox);

	ensure(MessageInputBox);
	MessageInputBox->OnTextCommitted.AddDynamic(this, &UOmokPlayUI::OnTextCommitted_DisplayMessage);
	MessageInputBox->SetClearKeyboardFocusOnCommit(false);

	ensure(SendButton);
	SendButton->OnClicked.AddDynamic(this, &UOmokPlayUI::OnClickedSendButton_DisplayMessage);

	ensure(CurrentRemainingTimeText);

	ensure(PlayerColorPanel);

	ensure(MenuOverlay);
	MenuOverlay->SetVisibility(ESlateVisibility::Hidden);
	MenuOverlay->SetIsEnabled(false);

	ensure(SurrenderButton);
	SurrenderButton->OnClicked.AddDynamic(this, &UOmokPlayUI::SwitchMenu);

	ensure(ResumeButton);
	ResumeButton->OnClicked.AddDynamic(this, &UOmokPlayUI::SwitchMenu);

	ensure(MatchEndOverlay);
	MatchEndOverlay->SetVisibility(ESlateVisibility::Hidden);
	MatchEndOverlay->SetIsEnabled(false);

	ensure(WinnerTextBlock);

	ensure(ResultTextBlock);

	ensure(TravelingTextBlock);
}

void UOmokPlayUI::OnTextCommitted_DisplayMessage(const FText& InText, ETextCommit::Type CommitType)
{
	if(ETextCommit::Type::OnEnter != CommitType)
	{
		return;
	}

	TObjectPtr<UOmokTextBlock> MessageBlock = NewObject<UOmokTextBlock>(this);
	
	MessageBlock->SetMessageAndConfig(
		InText,
		MessageScrollBox->GetCachedGeometry().GetLocalSize().X * 0.9f,
		OwningPlayerColor
	);

	MessageScrollBox->AddChild(MessageBlock);
	MessageInputBox->SetText(FText());
}

void UOmokPlayUI::OnClickedSendButton_DisplayMessage()
{
	TObjectPtr<UOmokTextBlock> MessageBlock = NewObject<UOmokTextBlock>(this);

	MessageBlock->SetMessageAndConfig(
		MessageInputBox->GetText(),
		MessageScrollBox->GetCachedGeometry().GetLocalSize().X * 0.9f,
		OwningPlayerColor
	);

	MessageScrollBox->AddChild(MessageBlock);
	MessageInputBox->SetText(FText());
}
