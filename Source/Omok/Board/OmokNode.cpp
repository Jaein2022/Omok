// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokNode.h"
#include "OmokBoard.h"

// Sets default values
AOmokNode::AOmokNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bFixed = false;
	//처음에는 고정시키면 안됨.

	this->NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NodeMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/Assets/Stone.Stone'")
	);
	ensure(NodeMeshRef.Succeeded());
	NodeMesh->SetStaticMesh(NodeMeshRef.Object);
}

void AOmokNode::SetClearColor(const uint8 InbWhite)
{
	if(bFixed)
	{
		return;
	}
	
	Color = FNodeColor::GetAllNodeColors()[InbWhite];
	NodeMaterialInstance->SetVectorParameterValue("NodeColor", FNodeColor::GetAllNodeColors()[InbWhite].ClearColor);
}

void AOmokNode::ReturnColor()
{
	if(bFixed)
	{
		return;
	}

	Color = FNodeColor::Transparent;

#if UE_BUILD_DEBUG
	NodeMaterialInstance->SetVectorParameterValue("NodeColor", FNodeColor::Transparent.FixColor);
#else
	NodeMaterialInstance->SetVectorParameterValue("NodeColor", FNodeColor::Transparent.ClearColor);
#endif

}

void AOmokNode::FixColor(const uint8 InbWhite)
{
	if(bFixed)
	{
		return;
	}

	Color = FNodeColor::GetAllNodeColors()[InbWhite];
	NodeMaterialInstance->SetVectorParameterValue("NodeColor", FNodeColor::GetAllNodeColors()[InbWhite].FixColor);
	bFixed = true;
}

void AOmokNode::SetCoordinate(const int32 X, const int32 Y)
{
	Coordinate.X = X;
	Coordinate.Y = Y;
}

void AOmokNode::SetNodeScale(const float InScale)
{
	NodeMesh->SetRelativeScale3D(FVector(InScale, InScale, InScale));
}

// Called when the game starts or when spawned
void AOmokNode::BeginPlay()
{
	Super::BeginPlay();

	NodeMaterialInstance = UMaterialInstanceDynamic::Create(
		LoadObject<UMaterial>(NULL, TEXT("/Script/Engine.Material'/Game/Assets/Materials/M_NodeMaterial.M_NodeMaterial'")),
		this
	);

	NodeMesh->SetMaterial(0, NodeMaterialInstance);

	Color = FNodeColor::Transparent;

#if UE_BUILD_DEBUG
	NodeMaterialInstance->SetVectorParameterValue("NodeColor", FNodeColor::Transparent.FixColor);
#else
	NodeMaterialInstance->SetVectorParameterValue("NodeColor", FNodeColor::Transparent.ClearColor);
#endif
}