﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokBoard.h"
#include "OmokNode.h"

// Sets default values
AOmokBoard::AOmokBoard(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//얘가 틱이 필요할까??

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/Assets/BoardMesh.BoardMesh'")
	);
	ensure(BoardMeshRef.Succeeded());
	ensure(BoardMesh->SetStaticMesh(BoardMeshRef.Object));

	RootComponent = BoardMesh;
	BoardMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	static ConstructorHelpers::FObjectFinder<UMaterial> LineMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/Materials/Line.Line'")
	);
	ensure(LineMaterialRef.Succeeded());
	BoardMesh->SetMaterial(0, LineMaterialRef.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> BoardMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/Materials/Board.Board'")
	);
	ensure(BoardMaterialRef.Succeeded());
	BoardMesh->SetMaterial(1, BoardMaterialRef.Object);

}

// Called every frame
void AOmokBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AOmokBoard::CheckWinningCondition(const TObjectPtr<AOmokNode> Node)
{
	ensure(HasAuthority());
	ensure(IsValid(Node));

	const int32 X = Node->GetCoordinate().X;
	const int32 Y = Node->GetCoordinate().Y;
	const ENodeColor Color = Node->GetNodeColor();

	//이번 돌에서 연결되는 직선들 중 가장 긴 것의 길이.
	const int32 LineLength = 1 + FMath::Max(
		TArray<int32>({
			CountNodes(X, Y + 1, Color, 0, 1) + CountNodes(X, Y - 1, Color, 0, -1),
			//수평 체크.

			CountNodes(X + 1, Y, Color, 1, 0) + CountNodes(X - 1, Y, Color, -1, 0),
			//수직 체크.

			CountNodes(X + 1, Y + 1, Color, 1, 1) + CountNodes(X - 1, Y - 1, Color, -1, -1),
			//사선 / 체크.

			CountNodes(X + 1, Y - 1, Color, 1, -1) + CountNodes(X - 1, Y + 1, Color, -1, 1)
			//사선 \ 체크.
		})
	);

	//같은색 돌이 5개 이상 연속되면 승리 처리.
	return (5 <= LineLength) ? true : false;
}

// Called when the game starts or when spawned
void AOmokBoard::BeginPlay()
{
	Super::BeginPlay();

	CreateAllNodes();
}

int32 AOmokBoard::CountNodes(
	const int32 X,
	const int32 Y,
	const ENodeColor Color,
	const int8 XDir,
	const int8 YDir
) const
{
	ensure(1 >= FMath::Abs(XDir));
	ensure(1 >= FMath::Abs(YDir));
	//XDir, YDir은 -1, 0, 1만 허용.

	ensure(Color == ENodeColor::Black || Color == ENodeColor::White);
	//Color는 Black과 White만 허용.

	if(0 > X || 15 <= X || 0 > Y || 15 <= Y)
	{
		return 0;
	}

	int32 CoordX = X;
	int32 CoordY = Y;
	int32 Length = 0;

	while(GetNode(CoordX, CoordY)->GetNodeColor() == Color)
	{
		Length++;

		CoordX += XDir;
		CoordY += YDir;

		if(0 > CoordX || 15 <= CoordX || 0 > CoordY || 15 <= CoordY)
		{
			break;
			//판을 벗어나면 종료.
		}
	}

	return Length;
}

void AOmokBoard::CreateAllNodes()
{
	const FVector2D InitLocation(-NodeDistance * 7, -NodeDistance * 7);	//좌하단 노드 위치.
	FActorSpawnParameters NodeSpawnParams;
	NodeSpawnParams.Owner = this;
	NodeSpawnParams.bNoFail = true;
	NodeSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FAttachmentTransformRules NodeAttachmentRules(EAttachmentRule::KeepRelative, false);

	AllNodes.Reserve(225);
	for(int32 x = 0; x < 15; x++)
	{
		for(int32 y = 0; y < 15; y++)
		{
			const FString NodeName(FString::Printf(TEXT("OmokNode %d, %d"), x, y));
			NodeSpawnParams.Name = FName(*NodeName);
			
			TObjectPtr<AOmokNode> NewNode = GetWorld()->SpawnActor<AOmokNode>(
				FVector(
					InitLocation.X + (x * NodeDistance), //+ GetActorLocation().X,
					InitLocation.Y + (y * NodeDistance), //+ GetActorLocation().Y,
					2.5f
				),
				GetActorUpVector().Rotation(),
				NodeSpawnParams
			);
			ensure(NewNode);
			NewNode->SetNodeScale(0.05f);
			NewNode->AttachToComponent(this->RootComponent, NodeAttachmentRules);
			NewNode->SetCoordinate(x, y);
			NewNode->SetActorLabel(NodeName);
			//Label: 액터가 언리얼 에디터 뷰포트에 배치되었을때 보이는 이름. Name과 다르다.

			AllNodes.Push(NewNode);
		}
	}
}