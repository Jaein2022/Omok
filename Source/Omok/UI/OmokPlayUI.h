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

	UFUNCTION()
	void ResetTimer(const uint8 InCurrentPlayerColor, const float ServerTimeSeconds, const float PlayTime);

	UFUNCTION()
	void UpdateTimerWithServer(const float ServerTimeSeconds);

	void UpdateTimerWithLocalDeltaTime(const float LocalDeltaSeconds);

	void SetOwningPlayerColor(const uint8 InbWhite);

	UFUNCTION()
	void SwitchMenu();

	void DisplayResult(const uint8 WinnerColor);



public: 
	FORCEINLINE const TObjectPtr<class UEditableTextBox> GetMessageInputbox() const { return MessageInputBox; }
	FORCEINLINE const TObjectPtr<class UButton> GetSendButton() const { return SendButton; }
	FORCEINLINE const TObjectPtr<class UButton> GetSurrenderButton() const { return SurrenderButton; }


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
	


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CurrentRemainingTimeText;

	float RemainingTime;

	float PrevServerTimeSeconds;

	uint8 CurrentPlayerColor;	//현재 플레이중인 플레이어의 색상.



private:
	UPROPERTY(meta = (Bindwidget))
	TObjectPtr<class UImage> PlayerColorPanel;	//이 UI를 소유하는 플레이어의 색상 표시 패널.



private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UOverlay> MenuOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ResumeButton; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SurrenderButton; 
	


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UOverlay> MatchEndOverlay; 

	UPROPERTY(meta = (Bindwidget))
	TObjectPtr<class UTextBlock> WinnerTextBlock;
	
	UPROPERTY(meta = (Bindwidget))
	TObjectPtr<class UTextBlock> ResultTextBlock;



private:
	uint8 OwningPlayerColor: 1;	//이 UI를 소유하는 플레이어의 색상. true: 백색.


	
};
