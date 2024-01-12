// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokHostingUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "../Player/OmokPlayerController.h"
#include "GameFramework/GameModeBase.h"


UOmokHostingUI::UOmokHostingUI(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer),
	JoinedText(FText::FromString(FString(TEXT("Joined!"))))
{
}

void UOmokHostingUI::SetIsEnabled(bool bInIsEnabled)
{
	Super::SetIsEnabled(bInIsEnabled);

	if(bInIsEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(
			TextChangeTimerHandle,
			TextChangeTimerDelegate,
			0.5f,
			true
		);

		WaitingTextIndex = 0;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TextChangeTimerHandle);
	}
}

void UOmokHostingUI::NativeConstruct()
{
	OwningPlayerController = CastChecked<AOmokPlayerController>(GetOwningPlayer());

	ensure(HostMenu);

	ensure(WaitingTextBlock);
	WaitingTextBlock->SetMinDesiredWidth(600);

	WaitingTexts.Reserve(4);
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting"))));
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting."))));
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting.."))));
	WaitingTexts.Emplace(FText::FromString(FString(TEXT("Waiting..."))));

	WaitingTextIndex = 0;

	WaitingTextBlock->SetText(WaitingTexts[0]);

	TextChangeTimerHandle.Invalidate();

	TextChangeTimerDelegate.BindUFunction(
		this,
		GET_FUNCTION_NAME_CHECKED(UOmokHostingUI, ChangeWaitingText)
	);

	ensure(ReadyButton);
	ReadyButton->OnClicked.AddDynamic(this, &UOmokHostingUI::OnClickedReadyButton);
	ReadyButton->SetIsEnabled(false);

	ensure(ReadyButtonTextBlock);
	ReadyButtonTextBlock->SetColorAndOpacity(FColor(100, 100, 100));

	ensure(CancelButton);
	CancelButton->OnClicked.AddDynamic(this, &UOmokHostingUI::OnClickedCancelButton);

	FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &UOmokHostingUI::OnJoinedClient);
	FGameModeEvents::GameModeLogoutEvent.AddUObject(this, &UOmokHostingUI::OnDisjoinedClient);
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

void UOmokHostingUI::OnClickedReadyButton()
{
	//플레이맵으로 이동.
}

void UOmokHostingUI::OnClickedCancelButton()
{
	GetWorld()->GetTimerManager().ClearTimer(TextChangeTimerHandle);

	OwningPlayerController->CancelHosting();
}

void UOmokHostingUI::OnJoinedClient(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	GetWorld()->GetTimerManager().ClearTimer(TextChangeTimerHandle);

	WaitingTextBlock->SetText(JoinedText);
	
	WaitingTextBlock->SetJustification(ETextJustify::Center);

	ReadyButtonTextBlock->SetColorAndOpacity(FColor::Black);
	
	ReadyButton->SetIsEnabled(true);
}

void UOmokHostingUI::OnDisjoinedClient(AGameModeBase* GameMode, AController* ExitingPlayer)
{
	GetWorld()->GetTimerManager().SetTimer(
		TextChangeTimerHandle,
		TextChangeTimerDelegate,
		0.5f,
		true
	);

	WaitingTextBlock->SetText(WaitingTexts[WaitingTextIndex]);

	WaitingTextBlock->SetJustification(ETextJustify::Left);

	ReadyButtonTextBlock->SetColorAndOpacity(FColor(100, 100, 100));
	
	ReadyButton->SetIsEnabled(false);
}
