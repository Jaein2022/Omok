// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokBoard.h"

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
	this->BoardMesh->SetRelativeScale3D(FVector(15.f, 15.f, 1.f));


	static ConstructorHelpers::FObjectFinder<UMaterial> BoardMaterialRef(
		TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'")
	);
	ensure(BoardMaterialRef.Succeeded());
	this->BoardMaterial = BoardMaterialRef.Object;


	this->BoardMesh->SetMaterial(0, this->BoardMaterial);
}

// Called when the game starts or when spawned
void AOmokBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOmokBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

