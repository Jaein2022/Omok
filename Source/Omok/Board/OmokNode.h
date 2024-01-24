// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Omok/Omok.h"
#include "OmokNode.generated.h"

//바둑알.
UCLASS()
class OMOK_API AOmokNode : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AOmokNode();

	void SetClearColor(const uint8 InbWhite);

	void ReturnColor();

	void FixColor(const uint8 InbWhite);

	void SetCoordinate(const int32 X, const int32 Y);

	void SetNodeScale(const float InScale);



public:
	FORCEINLINE const FIntVector2& GetCoordinate() const { return Coordinate; }
	FORCEINLINE const FNodeColor& GetNodeColor() const { return Color; }
	FORCEINLINE const bool IsFixed() const { return bFixed; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



protected:
	TObjectPtr<UStaticMeshComponent> NodeMesh;

	TObjectPtr<UMaterialInstanceDynamic> NodeMaterialInstance;



private:
	FNodeColor Color;	//현재 노드 색상.
	FIntVector2 Coordinate;	//노드 좌표. X++이 위, Y++이 오른쪽.

	bool bFixed;	//노드 색상 고정 됨/안됨.



};
