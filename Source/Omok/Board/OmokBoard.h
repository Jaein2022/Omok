// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmokBoard.generated.h"

//바둑판.
UCLASS()
class OMOK_API AOmokBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOmokBoard(const FObjectInitializer& ObjectInitializer);

	void FixNodeColor(const FIntVector2& InCoord, const uint8 InbWhite) const;

	

public:	
	FORCEINLINE TObjectPtr<class AOmokNode> GetNode(const int32 X, const int32 Y) const { return AllNodes[X * BoardSize + Y]; }
	FORCEINLINE TObjectPtr<class AOmokNode> GetNode(const FIntVector2 Coord) const { return AllNodes[Coord.X * BoardSize + Coord.Y]; }
	FORCEINLINE const TArray<TObjectPtr<class AOmokNode>>& GetAllNodes() { return AllNodes; }



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	//바둑알 생성 함수.
	void CreateAllNodes();



protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BoardMesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<TObjectPtr<class AOmokNode>> AllNodes;
	


private:
	const float NodeDistance = 12.5f;	//바둑알 간격. 
	const int32 BoardSize = 15;


};
