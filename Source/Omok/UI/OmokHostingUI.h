// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmokHostingUI.generated.h"

/**
 * 호스팅 UI 클래스.
 */
UCLASS()
class OMOK_API UOmokHostingUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UOmokHostingUI(const FObjectInitializer& ObjectInitializer);

	//Ready버튼 비활성화 시키고 Waiting 문자열 띄우는 함수.
	void SetWaiting();	

	//Ready버튼 활성화 시키고 Joined 문자열 띄우는 함수.
	void SetJoined();	

	void SetFlickeringOn();

	void SetFlickeringOff();

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

	//레벨 전환 절차 시작할 때.
	UFUNCTION()
	void OnNotifyPreLevelChange(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel);

	//Waiting 텍스트 변환 함수.
	UFUNCTION()
	void ChangeWaitingText();

	//Ready 글자 깜빡거리게 하는 함수.
	UFUNCTION()
	void FlickerReadyButtonText();


private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> HostMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WaitingTextBlock;

	FTimerHandle HostingUITimerHandle;

	FTimerDelegate TextChangeDelegate;

	TArray<FText> WaitingTexts;

	const FText JoinedText;

	uint8 WaitingTextIndex;

	UPROPERTY(meta = (BindingWidget))
	TObjectPtr<class UTextBlock> HostIPAddressBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ReadyButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ReadyButtonTextBlock;

	bool bFlickeringSwitch;

	FTimerDelegate FlickeringDelegate;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CancelButton;

};
