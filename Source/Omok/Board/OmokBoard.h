// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmokBoard.generated.h"

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

//바둑판.
UCLASS()
class OMOK_API AOmokBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOmokBoard(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	//같은색 바둑알이 5개 이상 연속으로 놓여 있는지 확인하는 함수. 서버 전용.
	bool CheckWinningCondition(const TObjectPtr<class AOmokNode> Node);



public:	
	FORCEINLINE TObjectPtr<class AOmokNode> GetNode(const int32 X, const int32 Y) const { return AllNodes[X * 15 + Y]; }
	FORCEINLINE TObjectPtr<class AOmokNode> GetNode(const FIntVector2 Coord) const { return AllNodes[Coord.X * 15 + Coord.Y]; }
	FORCEINLINE TArray<TObjectPtr<class AOmokNode>>& GetAllNodes() { return AllNodes; }



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/**
	* 주어진 좌표의 돌부터 상하좌우 대각선으로 같은 색의 바둑알이 얼마나 있는지 세는 함수.
	* @param X: 바둑알 X좌표.
	* @param Y: 바둑알 Y좌표.
	* @param Color: 바둑알의 색상. Black과 White만 넣을 것.
	* @param XDir: 1: 위쪽, -1: 아래쪽. 1, 0, -1만 입력할 것.
	* @param YDir: 1: 오른쪽, -1: 왼쪽. 1, 0, -1만 입력할 것.
	*/
	int32 CountNodes(const int32 X, const int32 Y, const ENodeColor Color, const int8 XDir, const int8 YDir) const;



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


};
