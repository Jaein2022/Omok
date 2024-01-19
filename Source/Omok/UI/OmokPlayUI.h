// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmokPlayUI.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API UOmokPlayUI : public UUserWidget
{
	GENERATED_BODY()

public:




public: 
	FORCEINLINE const TObjectPtr<class UEditableTextBox> GetChattingInputbox() const { return ChattingInputBox; }

	FORCEINLINE const TObjectPtr<class UButton> GetSendButton() const { return SendButton; }
	FORCEINLINE const TObjectPtr<class UTextBlock> GetBlackTimer() const { return BlackTimer; }
	FORCEINLINE const TObjectPtr<class UTextBlock> GetWhiteTimer() const { return WhiteTimer; }
	FORCEINLINE void SetColot(const bool bWhite) { bPlayerColor = bWhite; }

protected:
	virtual void NativeConstruct() override;



private:
	UFUNCTION()
	void OnTextCommitted_DisplayMessage(const FText& InText, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnClickedSendButton_DisplayMessage();


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> ChattingScrollBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> ChattingInputBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SendButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BlackTimer;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WhiteTimer;



private:
	bool bPlayerColor;	//true: 백색.
	
};
