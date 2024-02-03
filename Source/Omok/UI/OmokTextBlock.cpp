// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokTextBlock.h"
#include "Fonts/SlateFontInfo.h"
#include "Omok/Omok.h"

//const FSlateFontInfo UOmokTextBlock::MessageFontInfo = FSlateFontInfo(FCoreStyle::GetDefaultFont(), 24, TEXT("Regular"));

UOmokTextBlock::UOmokTextBlock()
{
	WrappingPolicy = ETextWrappingPolicy::AllowPerCharacterWrapping;
}

void UOmokTextBlock::SetMessageAndConfig(const FText& InText, const float Width, const uint8 bWhite)
{
	SetText(InText);
	SetFont(FSlateFontInfo(FCoreStyle::GetDefaultFont(), 24, TEXT("Regular")));
	SetColorAndOpacity(FNodeColor::GetAllNodeColors()[bWhite].FixColor);
	SetMinDesiredWidth(Width);
	WrapTextAt = Width;
}
