﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget));
	class UButton* Host;

	UPROPERTY(meta = (BindWidget));
	class UButton* Join;

	UPROPERTY(meta = (BindWidget));
	class UButton* Enter;

	UPROPERTY(meta = (BindWidget));
	class UButton* Back;

	UPROPERTY(meta = (BindWidget));
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget));
	class UWidget* SubMenu;

	UPROPERTY(meta = (BindWidget));
	class UWidget* MainMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	IMenuInterface* MenuInterface;

};

