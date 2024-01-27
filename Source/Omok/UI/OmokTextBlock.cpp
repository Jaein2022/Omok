﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokTextBlock.h"
#include "Fonts/SlateFontInfo.h"

//const FSlateFontInfo UOmokTextBlock::MessageFontInfo = FSlateFontInfo(FCoreStyle::GetDefaultFont(), 24, TEXT("Regular"));

UOmokTextBlock::UOmokTextBlock()
{
	WrappingPolicy = ETextWrappingPolicy::AllowPerCharacterWrapping;
}

void UOmokTextBlock::SetMessageAndConfig(const FText& InText, const float Width, const uint8 bWhite)
{
	SetText(InText);
	SetFont(FSlateFontInfo(FCoreStyle::GetDefaultFont(), 24, TEXT("Regular")));
	SetColorAndOpacity(bWhite ? FColor::White : FColor::Black);
	SetMinDesiredWidth(Width);
	WrapTextAt = Width;
}
