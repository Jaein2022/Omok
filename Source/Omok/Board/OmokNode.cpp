// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokNode.h"
#include "OmokBoard.h"


// Sets default values
AOmokNode::AOmokNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//얘도 틱 필요 없을것 같은데.

	bFixed = false;
	//처음에는 고정시키면 안됨.

	this->NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NodeMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/Assets/Stone.Stone'")
	);
	ensure(NodeMeshRef.Succeeded());
	NodeMesh->SetStaticMesh(NodeMeshRef.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> BlackMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/TempNodeMaterial/M_Black.M_Black'")
	);
	ensure(BlackMaterialRef.Succeeded());
	BlackMaterial = BlackMaterialRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> ClearBlackMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/TempNodeMaterial/M_ClearBlack.M_ClearBlack'")
	);
	ensure(ClearBlackMaterialRef.Succeeded());
	ClearBlackMaterial = ClearBlackMaterialRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> WhiteMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/TempNodeMaterial/M_White.M_White'")
	);
	ensure(WhiteMaterialRef.Succeeded());
	WhiteMaterial = WhiteMaterialRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> ClearWhiteMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/TempNodeMaterial/M_ClearWhite.M_ClearWhite'")
	);
	ensure(ClearWhiteMaterialRef.Succeeded());
	ClearWhiteMaterial = ClearWhiteMaterialRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> TransparentMaterialRef(
		TEXT("/Script/Engine.Material'/Game/Assets/TempNodeMaterial/M_Transparent.M_Transparent'")
	);
	ensure(TransparentMaterialRef.Succeeded());
	TransparentMaterial = TransparentMaterialRef.Object;

	SetNodeColor(ENodeColor::Transparent);
}

// Called every frame
void AOmokNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOmokNode::SetClearColor(const uint8 InbWhite)
{
	SetNodeColor(InbWhite ? ENodeColor::ClearWhite : ENodeColor::ClearBlack);
}

void AOmokNode::ReturnColor()
{
	SetNodeColor(ENodeColor::Transparent);
}

void AOmokNode::FixColor(const uint8 InbWhite)
{
	SetNodeColor(InbWhite ? ENodeColor::White : ENodeColor::Black);
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

}

void AOmokNode::SetNodeColor(ENodeColor NewColor)
{
	if(bFixed)
	{
		return;
	}

	Color = NewColor;

	switch(Color)
	{
	case ENodeColor::Black:
	{
		bFixed = true;
		NodeMesh->SetMaterial(0, BlackMaterial);
		break;
	}

	case ENodeColor::White:
	{
		bFixed = true;
		NodeMesh->SetMaterial(0, WhiteMaterial);
		break;
	}

	case ENodeColor::ClearBlack:
	{
		NodeMesh->SetMaterial(0, ClearBlackMaterial);
		break;
	}

	case ENodeColor::ClearWhite:
	{
		NodeMesh->SetMaterial(0, ClearWhiteMaterial);
		break;
	}

	case ENodeColor::Transparent:
	{
		NodeMesh->SetMaterial(0, TransparentMaterial);
		break;
	}

	case ENodeColor::Invalid:
	{
		check(false);
		break;
	}

	default:
		check(false);
		break;
	}
}


