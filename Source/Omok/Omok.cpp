// Copyright Epic Games, Inc. All Rights Reserved.

#include "Omok.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Omok, "Omok" );

TArray<FNodeColor> FNodeColor::AllNodeColors;

//인덱스 오름차순으로 생성할 것.

const FNodeColor FNodeColor::Black(TEXT("Black"), FLinearColor::Black, 0);
const FNodeColor FNodeColor::White(TEXT("White"), FLinearColor::White, 1);
const FNodeColor FNodeColor::Transparent(TEXT("Transparent"), FLinearColor(0.f, 0.f, 1.f, 0.5f), FLinearColor::Transparent, 2);