// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmokBoard.h"
#include "OmokNode.generated.h"

UENUM()
enum class ENodeColor: uint8
{
	Black,
	White,
	ClearBlack,
	ClearWhite,
	Transparent,
	Invalid
};

//바둑알.
UCLASS()
class OMOK_API AOmokNode : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AOmokNode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetClearColor(const uint8 InbWhite);

	void ReturnColor();

	void FixColor(const uint8 InbWhite);

	void SetCoordinate(const int32 X, const int32 Y);

	void SetNodeScale(const float InScale);


	

public:
	FORCEINLINE const FIntVector2& GetCoordinate() const { return Coordinate; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetNodeMesh() const { return NodeMesh; }
	FORCEINLINE const ENodeColor GetColor() const { return Color; }
	FORCEINLINE const bool IsFixed() const { return bFixed; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	void SetNodeColor(ENodeColor NewColor);


protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> NodeMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> BlackMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> ClearBlackMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> WhiteMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> ClearWhiteMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> TransparentMaterial;
	//진짜 투명이면 안보여서 지금은 반투명 파란색.



private:
	ENodeColor Color;	//현재 노드 색상.
	FIntVector2 Coordinate;	//노드 좌표. X++이 위, Y++이 오른쪽.

	bool bFixed;	//노드 색상 고정 됨/안됨.



};
