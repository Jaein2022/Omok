// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "OmokTextBlock.generated.h"

/**
 * UTextBlock에 래핑(들여쓰기) 관련 세팅만 재조정한 클래스. 
 */
UCLASS()
class OMOK_API UOmokTextBlock : public UTextBlock
{
	GENERATED_BODY()
	
public:
	UOmokTextBlock();

	void SetMessageAndConfig(const FText& InText, const float Width, const uint8 bWhite);



private:
	static struct FSlateFontInfo MessageFontInfo;
};
