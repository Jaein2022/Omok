// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokBoard.h"
#include "OmokNode.h"

// Sets default values
AOmokBoard::AOmokBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//얘가 틱이 필요할까??


	this->BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")
	);
	ensure(BoardMeshRef.Succeeded());
	ensure(this->BoardMesh->SetStaticMesh(BoardMeshRef.Object));

	this->BoardMesh->SetupAttachment(this->RootComponent);
	this->BoardMesh->SetRelativeScale3D(FVector(18.f, 18.f, 1.f));


	static ConstructorHelpers::FObjectFinder<UMaterial> BoardMaterialRef(
		TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'")
	);
	ensure(BoardMaterialRef.Succeeded());
	this->BoardMaterial = BoardMaterialRef.Object;


	this->BoardMesh->SetMaterial(0, this->BoardMaterial);

	NodeDistance = 100.f;

}

// Called when the game starts or when spawned
void AOmokBoard::BeginPlay()
{
	Super::BeginPlay();
	


	const FVector2D InitLocation(NodeDistance * 7, -NodeDistance * 7);	//좌상단 노드 위치.
	FActorSpawnParameters NodeSpawnParams;
	NodeSpawnParams.Owner = this;
	NodeSpawnParams.bNoFail = true;

	const FAttachmentTransformRules NodeAttachmentRules(EAttachmentRule::KeepWorld, false);

	AllNodes.Reserve(225);
	for(int32 x = 0; x < 15; x++)
	{
		for(int32 y = 0; y < 15; y++)
		{
			const FString NodeName(FString::Printf(TEXT("OmokNode %d, %d"), x, y));
			NodeSpawnParams.Name = FName(*NodeName);

			AllNodes.Push(
				GetWorld()->SpawnActor<AOmokNode>(
					FVector(
						InitLocation.X - (x * NodeDistance),
						InitLocation.Y + (y * NodeDistance), 
						100.f
					), 
					FRotator(),
					NodeSpawnParams
				)
			);

			AllNodes.Last()->AttachToComponent(this->RootComponent, NodeAttachmentRules);
			AllNodes.Last()->SetActorLabel(NodeName);
			//Label: 액터가 언리얼 에디터 뷰포트에 배치되었을때 보이는 이름. Name과 다르다.
		}
	}

}

// Called every frame
void AOmokBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

