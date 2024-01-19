// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokHostingUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameFramework/GameModeBase.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"


UOmokHostingUI::UOmokHostingUI(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer),
	JoinedText(FText::FromString(FString(TEXT("Joined!"))))
{
	IsTraveling = false;
}

void UOmokHostingUI::SetWaiting(const bool InbClientJoined /*= false*/)
{
	GetWorld()->GetTimerManager().SetTimer(
		HostingUITimerHandle,
		TextChangeDelegate,
		0.5f,
		true
	);

	WaitingTextIndex = 0;

	WaitingTextBlock->SetText(WaitingTexts[WaitingTextIndex]);
	WaitingTextBlock->SetJustification(ETextJustify::Left);

	if(false == InbClientJoined)
	{
		HostIPAddressBlock->SetVisibility(ESlateVisibility::Visible);
		HostIPAddressBlock->SetIsEnabled(true);

		ReadyButtonTextBlock->SetColorAndOpacity(FColor(100, 100, 100));
	}
	else
	{
		HostIPAddressBlock->SetVisibility(ESlateVisibility::Hidden);
		HostIPAddressBlock->SetIsEnabled(false);

		ReadyButtonTextBlock->SetColorAndOpacity(FColor::Black);
	}

	ReadyButton->SetIsEnabled(false);
}

void UOmokHostingUI::SetJoined()
{
	GetWorld()->GetTimerManager().ClearTimer(HostingUITimerHandle);

	WaitingTextBlock->SetText(JoinedText);
	WaitingTextBlock->SetJustification(ETextJustify::Center);

	HostIPAddressBlock->SetVisibility(ESlateVisibility::Hidden);
	HostIPAddressBlock->SetIsEnabled(false);

	ReadyButtonTextBlock->SetColorAndOpacity(FColor::Black);

	ReadyButton->SetIsEnabled(true);
	ReadyButton->SetVisibility(ESlateVisibility::Visible);
}

void UOmokHostingUI::SetFlickeringOn()
{
	GetWorld()->GetTimerManager().SetTimer(HostingUITimerHandle, FlickeringDelegate, 0.5f, true);
}

void UOmokHostingUI::SetFlickeringOff()
{
	GetWorld()->GetTimerManager().ClearTimer(HostingUITimerHandle);
}

void UOmokHostingUI::NativeConstruct()
{
	ensure(HostMenu);

	ensure(WaitingTextBlock);
	WaitingTextBlock->SetMinDesiredWidth(600);
	WaitingTextBlock->SetJustification(ETextJustify::Left);

	WaitingTexts.Reserve(4);
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting"))));
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting."))));
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting.."))));
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting..."))));

	WaitingTextIndex = 0;

	WaitingTextBlock->SetText(WaitingTexts[0]);

	HostingUITimerHandle.Invalidate();

	TextChangeDelegate.BindUObject(this, &UOmokHostingUI::ChangeWaitingText);

	ensure(HostIPAddressBlock);

	bool bCanBindAll = false;
	const FString HostIP = ISocketSubsystem::Get(	
	//주어진 플랫폼에 맞는 소켓 서브시스템을 가져오는 함수. "Sockets" 모듈 필요.
		PLATFORM_SOCKETSUBSYSTEM	//현재 플랫폼 이름.
	)->GetLocalHostAddr(			//로컬 호스트의 IP주소를 가져오는 함수.
		*GLog,						//로그 메세지를 출력할 디바이스.
		bCanBindAll					//true: 바인드 할 수 있는 IP주소만 가져온다. false: 전부 다 가져온다.
	)->ToString(false /*false: 포트는 생략한다.*/);

	HostIPAddressBlock->SetText(FText::FromString(TEXT("Host IP: ") + HostIP));

	ensure(ReadyButton);
	ReadyButton->OnClicked.AddDynamic(this, &UOmokHostingUI::OnClickedReadyButton);

	ReadyButton->SetIsEnabled(false);

	ensure(ReadyButtonTextBlock);
	ReadyButtonTextBlock->SetColorAndOpacity(FColor(100, 100, 100));
	

	bFlickeringSwitch = false;

	FlickeringDelegate.BindUObject(this, &UOmokHostingUI::FlickerReadyButtonText);

	ensure(CancelButton);
	CancelButton->OnClicked.AddDynamic(this, &UOmokHostingUI::OnClickedCancelButton);

	FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &UOmokHostingUI::OnJoinedClient);
	FGameModeEvents::GameModeLogoutEvent.AddUObject(this, &UOmokHostingUI::OnDisjoinedClient);

	GetGameInstance()->OnNotifyPreClientTravel().AddUObject(this, &UOmokHostingUI::OnNotifyPreLevelChange);
}

void UOmokHostingUI::OnClickedReadyButton()
{
	ReadyButton->SetIsEnabled(false);
}

void UOmokHostingUI::OnClickedCancelButton()
{
	GetWorld()->GetTimerManager().ClearTimer(HostingUITimerHandle);
}

void UOmokHostingUI::OnJoinedClient(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	SetJoined();
}

void UOmokHostingUI::OnDisjoinedClient(AGameModeBase* GameMode, AController* ExitingPlayer)
{
	SetWaiting(IsTraveling);
	IsTraveling = false;
}

void UOmokHostingUI::OnNotifyPreLevelChange(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel)
{
	SetWaiting(true);
	IsTraveling = true;
}

void UOmokHostingUI::ChangeWaitingText()
{
	WaitingTextBlock->SetText(WaitingTexts[WaitingTextIndex]);

	WaitingTextIndex++;
	if(WaitingTexts.Num() <= WaitingTextIndex)
	{
		WaitingTextIndex = 0;
	}
}

void UOmokHostingUI::FlickerReadyButtonText()
{
	ReadyButtonTextBlock->SetOpacity(bFlickeringSwitch ? 1.f : 0.f);
	bFlickeringSwitch = !bFlickeringSwitch;
}