// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmokBoard.generated.h"

UCLASS()
class OMOK_API AOmokBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOmokBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	float NodeDistance;	//노드간 간격.

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BoardMesh;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterial> BoardMaterial;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<TObjectPtr<class AOmokNode>> AllNodes;

};
