// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokGameStateBase.h"
#include "Board/OmokBoard.h"
#include "Board/OmokNode.h"

AOmokGameStateBase::AOmokGameStateBase()
{
	IsPlayerColorWhite = false;


}

void AOmokGameStateBase::CheckWinningCondition_Implementation(const AOmokNode* InCurrentNode)
{
	const int32 X = InCurrentNode->GetCoordinate().X;
	const int32 Y = InCurrentNode->GetCoordinate().Y;
	const ENodeColor Color = InCurrentNode->GetNodeColor();

	//이번 돌에서 연결되는 직선들 중 가장 긴 것의 길이.
	const int32 LineLength = 1 + FMath::Max(
		TArray<int32>({
			CountNodes(X, Y + 1, Color, 0, 1) + CountNodes(X, Y - 1, Color, 0, -1),
			//수평 체크.

			CountNodes(X + 1, Y, Color, 1, 0) + CountNodes(X - 1, Y, Color, -1, 0),
			//수직 체크.

			CountNodes(X + 1, Y + 1, Color, 1, 1) + CountNodes(X - 1, Y - 1, Color, -1, -1),
			//사선 체크 1.

			CountNodes(X + 1, Y - 1, Color, 1, -1) + CountNodes(X - 1, Y + 1, Color, -1, 1)
			//사선 체크 2.
		})
	);

	if(5 <= LineLength)
	{
		FString Result;
		if(Color == ENodeColor::Black)
		{
			Result = TEXT("Black Wins!");
		}
		else if(Color == ENodeColor::White)
		{
			Result = TEXT("White Wins!");
		}

		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, *Result);
		//같은색 돌이 5개 이상 연속되면 승리 처리.
	}
}

int32 AOmokGameStateBase::CountNodes(
	const int32 InCoordinateX,
	const int32 InCoordinateY,
	const ENodeColor InColor,
	const int8 XDirection,
	const int8 YDirection
)
{
	ensure(1 >= FMath::Abs(XDirection));
	ensure(1 >= FMath::Abs(YDirection));
	//XDirection, YDirection은 -1, 0, 1만 허용.

	if(0 > InCoordinateX || 15 <= InCoordinateX || 0 > InCoordinateY || 15 <= InCoordinateY)
	{
		return 0;
	}

	int32 CoordX = InCoordinateX;
	int32 CoordY = InCoordinateY;
	int32 Length = 0;

	while(OmokBoard->GetNode(CoordX, CoordY)->GetNodeColor() == InColor)
	{
		Length++;

		CoordX += XDirection;
		CoordY += YDirection;

		if(0 > CoordX || 15 <= CoordX || 0 > CoordY || 15 <= CoordY)
		{
			break;
			//판을 벗어나면 종료.
		}
	}

	return Length;
}

void AOmokGameStateBase::CreateOmokBoard_Implementation(
	const FVector& BoardLocation,
	UMaterial* InLineMaterial,
	UMaterial* InBoardMaterial,
	UMaterial* InNodeBlackMaterial,
	UMaterial* InNodeClearBlackMaterial,
	UMaterial* InNodeWhiteMaterial,
	UMaterial* InNodeClearWhiteMaterial,
	UMaterial* InNodeClearMaterial
)
{
	//const FString CurrentMapName = GetWorld()->GetMapName().RightChop(GetWorld()->StreamingLevelsPrefix.Len());
	////GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, CurrentMapName);

	//ensure(TEXT("PlayMap") == CurrentMapName);
	////이 함수는 플레이맵에서만 호출해야하는 함수.

	ensure(GetLevel());

	OmokBoard = GetWorld()->SpawnActor<AOmokBoard>(BoardLocation, FRotator(0, 0, 0));
	OmokBoard->SetLineMaterial(InLineMaterial);
	OmokBoard->SetBoardMaterial(InBoardMaterial);
	OmokBoard->SetNodeMaterials(
		InNodeBlackMaterial,
		InNodeClearBlackMaterial,
		InNodeWhiteMaterial,
		InNodeClearWhiteMaterial,
		InNodeClearMaterial
	);

}
