// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

//UCLASS() <- FOmokDevelopmentSupport.generated.h를 생성하지 않았으므로 사용할 수 없음.
class OMOK_API FOmokDevelopmentSupport
{
	//OMOK_API <- 언리얼 엔진에서 제공하는 다른 모듈이나 라이브러리를 참조하는데 필요한 매크로.

	//GENERATED_BODY() <- FOmokDevelopmentSupport.generated.h를 생성하지 않았으므로 사용할 수 없음.
public:

	/**
	* 화면에 디버그 메세지 띄우는 함수.
	* @param Caller: 이 함수를 호출한 액터 인스턴스.
	* @param CallingFunc: 이 함수가 호출된 함수 스코프. __FUNCTION__ 넣으면 됨.
	* @param Message: 띄울 메세지.
	* @param TimeToDisplay: 메세지를 띄우고 있을 시간.
	* @param DisplayColor: 글자 색.
	*/
	static void DisplayDebugMessageForActors(
		const AActor* Caller,
		const FString& CallingFunc,
		const FString& Message,
		const float TimeToDisplay = 4.0f,
		const FColor DisplayColor = FColor::Red
	)
	{
		ensureMsgf(Caller, TEXT("%s"), TEXT("This function is only for actors."));

		FString NetModeInfo;
		switch(Caller->GetNetMode())
		{
			case NM_Standalone:
				NetModeInfo = TEXT("Stand Alone");
				break;

			case NM_DedicatedServer:
				NetModeInfo = TEXT("Dedicated Server");
				break;

			case NM_ListenServer:
				NetModeInfo = TEXT("Listen Server");
				break;

			case NM_Client:
				NetModeInfo = TEXT("Client");
				break;


			case NM_MAX:
				ensure(false);
				break;

			default:
				ensure(false);
				break;
		}

		GEngine->AddOnScreenDebugMessage(
			-1,
			TimeToDisplay,
			DisplayColor,
			*FString::Printf(
				TEXT("%s: [%s][%s/%s] %s() %s"),
				*Caller->GetName(),
				*NetModeInfo,
				*UEnum::GetValueAsString(TEXT("Engine.ENetRole"), Caller->GetLocalRole()),
				*UEnum::GetValueAsString(TEXT("Engine.ENetRole"), Caller->GetRemoteRole()),
				*CallingFunc,
				*Message
			)
		);
	}
};
