// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmokPlayUI.generated.h"

//플레이 레벨 UI 클래스.
UCLASS()
class OMOK_API UOmokPlayUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void DisplayReceivedMessage(const FText& InText, const uint8 bColor);



public: 
	FORCEINLINE const TObjectPtr<class UEditableTextBox> GetMessageInputbox() const { return MessageInputBox; }
	FORCEINLINE const TObjectPtr<class UButton> GetSendButton() const { return SendButton; }
	FORCEINLINE const TObjectPtr<class UTextBlock> GetBlackTimer() const { return BlackTimer; }
	FORCEINLINE const TObjectPtr<class UTextBlock> GetWhiteTimer() const { return WhiteTimer; }
	FORCEINLINE void SetOwningPlayerColor(const uint8 InbWhite) { bOwningPlayerColor = InbWhite; }



protected:
	virtual void NativeConstruct() override;



private:
	UFUNCTION()
	void OnTextCommitted_DisplayMessage(const FText& InText, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnClickedSendButton_DisplayMessage();



private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> MessageScrollBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> MessageInputBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SendButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BlackTimer;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WhiteTimer;



private:
	uint8 bOwningPlayerColor;	//true: 백색.
	
};
