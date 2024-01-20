// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Omok/UI/OmokTextBlock.h"

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

void UOmokPlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(MessageScrollBox);

	ensure(MessageInputBox);
	MessageInputBox->OnTextCommitted.AddDynamic(this, &UOmokPlayUI::OnTextCommitted_DisplayMessage);
	MessageInputBox->SetClearKeyboardFocusOnCommit(false);

	ensure(SendButton);
	SendButton->OnClicked.AddDynamic(this, &UOmokPlayUI::OnClickedSendButton_DisplayMessage);

	ensure(BlackTimer);

	ensure(WhiteTimer);
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
		bOwningPlayerColor
	);

	MessageScrollBox->AddChild(MessageBlock);
	MessageInputBox->SetText(FText());
	//ChattingScrollBox->RemoveChild();
}

void UOmokPlayUI::OnClickedSendButton_DisplayMessage()
{
	TObjectPtr<UOmokTextBlock> MessageBlock = NewObject<UOmokTextBlock>(this);

	MessageBlock->SetMessageAndConfig(
		MessageInputBox->GetText(),
		MessageScrollBox->GetCachedGeometry().GetLocalSize().X * 0.9f,
		bOwningPlayerColor
	);

	MessageScrollBox->AddChild(MessageBlock);
	MessageInputBox->SetText(FText());
}
