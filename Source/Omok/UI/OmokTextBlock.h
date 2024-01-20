// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "OmokTextBlock.generated.h"

/**
 * UTextBlock에 래핑(들여쓰기) 관련 세팅만 내 마음대로 할 수 있게 만든 클래스. 
 */
UCLASS()
class OMOK_API UOmokTextBlock : public UTextBlock
{
	GENERATED_BODY()
	
public:
	UOmokTextBlock();

	void SetMessageAndConfig(const FText& InText, const float Width, const uint8 bWhite);



private:
	static struct FSlateFontInfo MessageFontInfo;	//폰트 정보 저장 구조체.
	//모든 텍스트블록들이 동일한 폰트 정보를 사용하므로 정적 변수 하나를 공유하게 한다.
};
