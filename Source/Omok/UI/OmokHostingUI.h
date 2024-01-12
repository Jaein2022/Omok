// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmokHostingUI.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API UOmokHostingUI : public UUserWidget
{
	GENERATED_BODY()

	//호스팅 UI 클래스.

public:
	UOmokHostingUI(const FObjectInitializer& ObjectInitializer);

	virtual void SetIsEnabled(bool bInIsEnabled) override;

protected:
	virtual void NativeConstruct() override;


private:
	UFUNCTION()
	void OnClickedReadyButton();

	UFUNCTION()
	void OnClickedCancelButton();


private:
	UFUNCTION()
	void OnJoinedClient(AGameModeBase* GameMode, APlayerController* NewPlayer);

	UFUNCTION()
	void OnDisjoinedClient(AGameModeBase* GameMode, AController* ExitingPlayer);


private:
	UFUNCTION()
	void ChangeWaitingText();


private:
	TObjectPtr<class AOmokPlayerController> OwningPlayerController;


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> HostMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WaitingTextBlock;

	FTimerHandle TextChangeTimerHandle;

	FTimerDelegate TextChangeTimerDelegate;

	TArray<FText> WaitingTexts;

	const FText JoinedText;

	uint8 WaitingTextIndex;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ReadyButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ReadyButtonTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CancelButton;

};
