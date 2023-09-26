// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokBoard.h"
#include "OmokNode.h"

// Sets default values
AOmokBoard::AOmokBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//얘가 틱이 필요할까??

	NodeDistance = 235.f;


	this->BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/Assets/BoardA.BoardA'")
	);
	ensure(BoardMeshRef.Succeeded());
	ensure(this->BoardMesh->SetStaticMesh(BoardMeshRef.Object));

	this->BoardMesh->SetupAttachment(this->RootComponent);
	this->BoardMesh->SetRelativeScale3D(FVector(19.f, 19.f, 1.f));


}

// Called when the game starts or when spawned
void AOmokBoard::BeginPlay()
{
	Super::BeginPlay();
	


	const FVector2D InitLocation(NodeDistance * 7, -NodeDistance * 7);	//좌상단 노드 위치.
	FActorSpawnParameters NodeSpawnParams;
	NodeSpawnParams.Owner = this;
	NodeSpawnParams.bNoFail = true;
	NodeSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
						30.f
					), 
					FRotator(),
					NodeSpawnParams
				)
			);

			AllNodes.Last()->AttachToComponent(this->RootComponent, NodeAttachmentRules);
			AllNodes.Last()->SetMaterials(NodeMaterials);
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

void AOmokBoard::SetLineMaterial(TObjectPtr<UMaterial> InLineMaterial)
{
	this->LineMaterial = InLineMaterial;
	this->BoardMesh->SetMaterial(0, this->LineMaterial);
}

void AOmokBoard::SetBoardMaterial(TObjectPtr<UMaterial> InBoardMaterial)
{
	this->BoardMaterial = InBoardMaterial;
	this->BoardMesh->SetMaterial(1, this->BoardMaterial);
}

void AOmokBoard::SetNodeMaterials(
	TObjectPtr<UMaterial> BlackMaterial,
	TObjectPtr<UMaterial> ClearBlackMaterial,
	TObjectPtr<UMaterial> WhiteMaterial,
	TObjectPtr<UMaterial> ClearWhiteMaterial,
	TObjectPtr<UMaterial> ClearMaterial
)
{
	NodeMaterials.Reserve(5);
	NodeMaterials.Add(BlackMaterial);
	NodeMaterials.Add(ClearBlackMaterial);
	NodeMaterials.Add(WhiteMaterial);
	NodeMaterials.Add(ClearWhiteMaterial);
	NodeMaterials.Add(ClearMaterial);
}

