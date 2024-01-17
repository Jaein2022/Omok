﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmokLobbyUI.generated.h"

/**
 * 로비 UI 클래스.
 */
UCLASS()
class OMOK_API UOmokLobbyUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UOmokLobbyUI(const FObjectInitializer& ObjectInitializer);

	void ShowJoinMenu() const;

	const FString& GetIPAddress() const;

	FORCEINLINE const TObjectPtr<class UButton> GetHostButton() const { return HostButton; }
	FORCEINLINE const TObjectPtr<class UButton> GetQuitButton() const { return QuitButton; }
	FORCEINLINE const TObjectPtr<class UButton> GetEnterButton() const { return EnterButton; }
	FORCEINLINE const TObjectPtr<class UButton> GetBackButton() const { return BackButton; }
	FORCEINLINE static void SwitchToJoinMenu() { bRetunedFromHost = true; }

protected:
	virtual void NativeConstruct() override;


private:
	UFUNCTION()
	void OnClickedJoinButton();
	
	UFUNCTION()
	void OnClickedBackButton();



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
	TObjectPtr<class UEditableTextBox> IPAddressBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> EnterButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BackButton;



private:
	//true: 클라이언트 PC가 HostingLevel에서 접속을 끊고 돌아왔음. 그래서 MainMenu가 아니라 JoinMenu를 보여줘야 함.
	static bool bRetunedFromHost;	
};
