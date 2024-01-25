// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokBoard.h"
#include "OmokNode.h"

// Sets default values
AOmokBoard::AOmokBoard(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

void AOmokBoard::FixNodeColor(const FIntVector2& InCoord, const uint8 InbWhite) const
{
	GetNode(InCoord)->FixColor(InbWhite);
}

// Called when the game starts or when spawned
void AOmokBoard::BeginPlay()
{
	Super::BeginPlay();

	CreateAllNodes();
}

void AOmokBoard::CreateAllNodes()
{
	const FVector2D InitLocation(-NodeDistance * (BoardSize / 2), -NodeDistance * (BoardSize / 2));	//좌하단 노드 위치.
	FActorSpawnParameters NodeSpawnParams;
	NodeSpawnParams.Owner = this;
	NodeSpawnParams.bNoFail = true;
	NodeSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FAttachmentTransformRules NodeAttachmentRules(EAttachmentRule::KeepRelative, false);

	AllNodes.Reserve(BoardSize * BoardSize);
	for(int32 x = 0; x < BoardSize; x++)
	{
		for(int32 y = 0; y < BoardSize; y++)
		{
			const FString NodeName(FString::Printf(TEXT("OmokNode %d, %d"), x, y));
			NodeSpawnParams.Name = FName(*NodeName);
			
			TObjectPtr<AOmokNode> NewNode = GetWorld()->SpawnActor<AOmokNode>(
				FVector(
					InitLocation.X + (x * NodeDistance), 
					InitLocation.Y + (y * NodeDistance), 
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