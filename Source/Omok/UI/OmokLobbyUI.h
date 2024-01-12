// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmokLobbyUI.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API UOmokLobbyUI : public UUserWidget
{
	GENERATED_BODY()
	
	//로비 UI 클래스.

	friend class AOmokPlayerController;

public:
	UOmokLobbyUI(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeConstruct() override;


private:
	UFUNCTION()
	void OnClickedHostButton();

	UFUNCTION()
	void OnClickedJoinButton();

	UFUNCTION()
	void OnClickedQuitButton();

	UFUNCTION()
	void OnClickedEnterButton();
	
	UFUNCTION()
	void OnClickedBackButton();

	//UFUNCTION()
	//void OnClickedReadyButton();

	//UFUNCTION()
	//void OnClickedCancelButton();


private:
	//UFUNCTION()
	//void FlickerReadyButtonText();


private:
	TObjectPtr<class AOmokPlayerController> OwningPlayerController;


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> MainMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HostButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> JoinButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> JoinMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> IPAddress;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> EnterButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BackButton;


//private:
//	UPROPERTY(meta = (BindWidget))
//	TObjectPtr<class UVerticalBox> ReadyMenu;
//
//	UPROPERTY(meta = (BindWidget))
//	TObjectPtr<class UButton> ReadyButton;
//
//	UPROPERTY(meta = (BindWidget))
//	TObjectPtr<class UTextBlock> ReadyButtonTextBlock;
//
//	FTimerHandle TextFlickeringTimerHandle;
//
//	FTimerDelegate FTextFlickeringTimerDelegate;
//
//	bool bFlickeringSwitch;
//
//	UPROPERTY(meta = (BindWidget))
//	TObjectPtr<class UButton> CancelButton;
};
