// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokNode.h"

// Sets default values
AOmokNode::AOmokNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//얘도 틱 필요 없을것 같은데.

	IsFixed = false;
	//처음에는 고정시키면 안됨.

	this->NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NodeMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/Assets/Stone.Stone'")
	);
	ensure(NodeMeshRef.Succeeded());
	NodeMesh->SetStaticMesh(NodeMeshRef.Object);
	NodeMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

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


	BeginCursorOverlapDelegate.BindUFunction(this, "OnBeginCursorOverlap");
	NodeMesh->OnBeginCursorOver.Add(BeginCursorOverlapDelegate);
	
	EndCursorOverlapDelegate.BindUFunction(this, "OnEndCursorOverlap");
	NodeMesh->OnEndCursorOver.Add(EndCursorOverlapDelegate);
	
	ClickDelegate.BindUFunction(this, "OnClick");
	NodeMesh->OnClicked.Add(ClickDelegate);

}

// Called when the game starts or when spawned
void AOmokNode::BeginPlay()
{
	Super::BeginPlay();
	
	//OmokGameState = CastChecked<AOmokGameStateBase>(GetWorld()->GetGameState());
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
		NodeMesh->SetMaterial(0, ClearBlackMaterial);
		break;
	}

	case ENodeColor::White:
	{
		NodeMesh->SetMaterial(0, WhiteMaterial);
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

void AOmokNode::OnBeginCursorOverlap()
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("OverlapBegin!"));

	if(true == IsFixed)
	{
		return;
	}

	//SetNodeColor(OmokGameState->GetIsPlayerColorWhite() ? ENodeColor::ClearWhite : ENodeColor::ClearBlack);
	SetNodeColor(ENodeColor::ClearBlack);
}

void AOmokNode::OnEndCursorOverlap()
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("OverlapEnd!"));

	if(true == IsFixed)
	{
		return;
	}

	SetNodeColor(ENodeColor::Transparent);
}

void AOmokNode::OnClick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Click!"));

	if(true == IsFixed)
	{
		return;
	}

	//SetNodeColor(OmokGameState->GetIsPlayerColorWhite() ? ENodeColor::White : ENodeColor::Black);
	SetNodeColor(ENodeColor::Black);

	IsFixed = true;
	//OmokGameState->CheckWinningCondition(this);
	Board->CheckWinningCondition(this);
}

void AOmokNode::SetCoordinate(int32 X, int32 Y)
{
	Coordinate.X = X;
	Coordinate.Y = Y;
}

