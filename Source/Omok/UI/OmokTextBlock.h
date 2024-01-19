// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "OmokTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API UOmokTextBlock : public UTextBlock
{
	GENERATED_BODY()
	
public:
	void SetMessage(const FText& InText, const float Width, const bool bWhite);

public:
	FORCEINLINE void SetWrappingPolicy(const ETextWrappingPolicy InWrappingPolicy) { WrappingPolicy = InWrappingPolicy; }
	FORCEINLINE void SetWrapTextAt(const float InWrapTextAt) { WrapTextAt = InWrapTextAt; }

};
