// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"


USTRUCT(NoExport)
struct OMOK_API FNodeColor
{
	//GENERATED_BODY()

	FNodeColor(): Name(FText()), FixColor(FLinearColor(1.f, 0.f, 0.f, 0.5f)), ClearColor(FLinearColor::Transparent), Index(255)
	{
	}
	
	FNodeColor(const FNodeColor& Other): Name(Other.Name), FixColor(Other.FixColor), ClearColor(Other.ClearColor), Index(Other.Index)
	{
	}
	
	FNodeColor(FNodeColor&& Other): Name(Other.Name), FixColor(Other.FixColor), ClearColor(Other.ClearColor), Index(Other.Index)
	{
	}



private:
	FNodeColor(const FString& InName, const FLinearColor& InColor, const uint8 InIndex):
		Name(FText::FromString(InName)), FixColor(InColor), ClearColor(InColor.R, InColor.G, InColor.B, 0.75f), Index(InIndex)
	{
		ensure(static_cast<int32>(this->Index) == AllNodeColors.Num());
		AllNodeColors.Add(*this);
	}
	
	FNodeColor(const FString& InName, const FLinearColor& InColor, const FLinearColor& InClearColor, const uint8 InIndex):
		Name(FText::FromString(InName)), FixColor(InColor), ClearColor(InClearColor), Index(InIndex)
	{
		ensure(static_cast<int32>(this->Index) == AllNodeColors.Num());
		AllNodeColors.Add(*this);
	}



public:
	bool operator==(const FNodeColor& InNodeColor)
	{
		return this->Index == InNodeColor.Index;
	}

	bool operator!=(const FNodeColor& InNodeColor)
	{
		return this->Index != InNodeColor.Index;
	}

	bool operator==(const uint8 InIndex) const
	{
		return Index == InIndex;
	}

	bool operator!=(const uint8 InIndex) const
	{
		return Index != InIndex;
	}

	bool operator==(const FLinearColor& InColor) const
	{
		return FixColor.Equals(InColor);
	}

	bool operator!=(const FLinearColor& InColor) const
	{
		return !FixColor.Equals(InColor);
	}

	bool operator==(const FText& InName) const
	{
		return Name.EqualToCaseIgnored(InName);
	}

	bool operator!=(const FText& InName) const
	{
		return !Name.EqualToCaseIgnored(InName);
	}

	FNodeColor& operator=(FNodeColor&& Other) = default;
	
	FNodeColor& operator=(const FNodeColor& Other) = default;

	

public:
	static const TArray<FNodeColor>& GetAllNodeColors()
	{
		return AllNodeColors;
	}


public:
	FText Name;
	FLinearColor FixColor;
	FLinearColor ClearColor;
	uint8 Index;



public:
	static const FNodeColor Black;
	static const FNodeColor White;
	static const FNodeColor Transparent;



private:
	static TArray<FNodeColor> AllNodeColors;



};

//개발 지원 기능만 모아둔 클래스.
class OMOK_API FOmokDevelopmentSupport
//UCLASS() <- FOmokDevelopmentSupport.generated.h를 생성하지 않았으므로 사용할 수 없음.
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
		ensureMsgf(IsValidChecked(Caller), TEXT("%s"), TEXT("This function is only for actors."));

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
