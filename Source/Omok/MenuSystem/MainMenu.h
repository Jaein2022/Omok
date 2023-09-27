// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
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
	class UButton* Quit;

	UPROPERTY(meta = (BindWidget));
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget));
	class UWidget* SubMenu;

	UPROPERTY(meta = (BindWidget));
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget));
	class UEditableTextBox* IpText;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitPressed();
};

