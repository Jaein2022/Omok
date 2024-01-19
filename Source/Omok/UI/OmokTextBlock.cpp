// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokTextBlock.h"
#include "Fonts/SlateFontInfo.h"

void UOmokTextBlock::SetTextAndWidth(const FText& InText, const float Width, const bool bWhite)
{
	SetText(InText);
	Font.Size = 24;
	SetColorAndOpacity(bWhite ? FColor::White : FColor::Black);
	SetMinDesiredWidth(Width);
	SetWrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping);
	SetWrapTextAt(Width);
}
