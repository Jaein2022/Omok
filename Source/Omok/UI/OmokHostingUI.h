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

	//friend class AOmokPlayerController;

public:
	UOmokHostingUI(const FObjectInitializer& ObjectInitializer);

	virtual void SetIsEnabled(bool bInIsEnabled) override;

	//Ready버튼 비활성화 시키고 Waiting 문자열 띄우는 함수.
	void SetWaiting();	

	//Ready버튼 활성화 시키고 Joined 문자열 띄우는 함수.
	void SetJoined();	

	FORCEINLINE const TObjectPtr<class UButton> GetCancelButton() const { return CancelButton; }
	FORCEINLINE const TObjectPtr<class UButton> GetReadyButton() const { return ReadyButton; }

protected:
	virtual void NativeConstruct() override;


private:
	UFUNCTION()
	void OnClickedCancelButton();


private:
	//클라이언트가 들어왔을 때.
	UFUNCTION()
	void OnJoinedClient(AGameModeBase* GameMode, APlayerController* NewPlayer);

	//클라이언트가 나갔을 때.
	UFUNCTION()
	void OnDisjoinedClient(AGameModeBase* GameMode, AController* ExitingPlayer);


private:
	UFUNCTION()
	void ChangeWaitingText();


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

	UPROPERTY(meta = (BindingWidget))
	TObjectPtr<class UTextBlock> HostIPAddressBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ReadyButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ReadyButtonTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CancelButton;

};
