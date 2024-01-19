// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokPlayUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Omok/UI/OmokTextBlock.h"

void UOmokPlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(ChattingScrollBox);

	ensure(ChattingInputBox);
	ChattingInputBox->OnTextCommitted.AddDynamic(this, &UOmokPlayUI::OnTextCommitted_DisplayMessage);
	ChattingInputBox->SetClearKeyboardFocusOnCommit(false);
	//ChattingInputBox->SetSelectAllTextWhenFocused(true);

	ensure(SendButton);
	SendButton->OnClicked.AddDynamic(this, &UOmokPlayUI::OnClickedSendButton_DisplayMessage);

	ensure(BlackTimer);

	ensure(WhiteTimer);
}

void UOmokPlayUI::OnTextCommitted_DisplayMessage(const FText& InText, ETextCommit::Type CommitMethod)
{
	if(ETextCommit::Type::OnEnter != CommitMethod)
	{
		return;
	}

	TObjectPtr<UOmokTextBlock> Message = NewObject<UOmokTextBlock>(this);
	
	Message->SetMessage(
		InText,
		ChattingScrollBox->GetCachedGeometry().GetLocalSize().X * 0.9f,
		bPlayerColor
	);
	
	//auto temp = ChattingScrollBox->GetCachedGeometry().GetLocalSize();
	//auto temp1 = ChattingScrollBox->GetCachedGeometry().GetAbsoluteSize();
	//auto temp2 = ChattingScrollBox->GetDesiredSize();

	ChattingScrollBox->AddChild(Message);
	ChattingInputBox->SetText(FText());
	//ChattingScrollBox->RemoveChild();
}

void UOmokPlayUI::OnClickedSendButton_DisplayMessage()
{
	TObjectPtr<UOmokTextBlock> Message = NewObject<UOmokTextBlock>(this);

	Message->SetMessage(
		ChattingInputBox->GetText(),
		ChattingScrollBox->GetCachedGeometry().GetLocalSize().X * 0.9f,
		bPlayerColor
	);

	ChattingScrollBox->AddChild(Message);
	ChattingInputBox->SetText(FText());
}
