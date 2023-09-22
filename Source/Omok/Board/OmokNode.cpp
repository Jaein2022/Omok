// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokNode.h"
#include "../OmokPlayerController.h"

// Sets default values
AOmokNode::AOmokNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//얘도 틱 필요 없을것 같은데.

	this->NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NodeMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'")
	);
	ensure(NodeMeshRef.Succeeded());
	NodeMesh->SetStaticMesh(NodeMeshRef.Object);
	NodeMesh->SetWorldScale3D(FVector(1.f, 1.f, 0.2f));

	static ConstructorHelpers::FObjectFinder<UMaterial> BlackMaterialRef(
		TEXT("/Script/Engine.Material'/Game/NodeMaterial/M_Black.M_Black'")
	);
	ensure(BlackMaterialRef.Succeeded());
	BlackMaterial = BlackMaterialRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> WhiteMaterialRef(
		TEXT("/Script/Engine.Material'/Game/NodeMaterial/M_White.M_White'")
	);
	ensure(WhiteMaterialRef.Succeeded());
	WhiteMaterial = WhiteMaterialRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> TransparentMaterialRef(
		TEXT("/Script/Engine.Material'/Game/NodeMaterial/M_Transparent.M_Transparent'")
	);
	ensure(TransparentMaterialRef.Succeeded());
	ClearMaterial = TransparentMaterialRef.Object;

	SetNodeColor(ENodeColor::Clear);


	BeginCursorOverlapDelegate.BindUFunction(this, "ReactOnBeginCursorOverlap");
	NodeMesh->OnBeginCursorOver.Add(BeginCursorOverlapDelegate);
	
	EndCursorOverlapDelegate.BindUFunction(this, "ReactOnEndCursorOverlap");
	NodeMesh->OnEndCursorOver.Add(EndCursorOverlapDelegate);
	
	ClickDelegate.BindUFunction(this, "ReactOnClick");
	NodeMesh->OnClicked.Add(ClickDelegate);

	//NodeMesh->OnBeginCursorOver.

}

// Called when the game starts or when spawned
void AOmokNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOmokNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

void AOmokNode::SetNodeColor(ENodeColor NewColor)
{
	CurrentColor = NewColor;

	switch(CurrentColor)
	{
	case ENodeColor::Black:
	{
		NodeMesh->SetMaterial(0, BlackMaterial);
		break;
	}
		
	case ENodeColor::ClearBlack:
	{

		break;
	}

	case ENodeColor::White:
	{
		NodeMesh->SetMaterial(0, WhiteMaterial);
		break;
	}

	case ENodeColor::ClearWhite:
	{

		break;
	}

	case ENodeColor::Clear:
	{
		NodeMesh->SetMaterial(0, ClearMaterial);
		break;
	}

	default:
		break;
	}


}

void AOmokNode::ReactOnBeginCursorOverlap()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("OverlapBegin!"));
}

void AOmokNode::ReactOnEndCursorOverlap()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("OverlapEnd!"));
}

void AOmokNode::ReactOnClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Click!"));
}

