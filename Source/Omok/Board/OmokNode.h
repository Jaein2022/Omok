﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../OmokGameStateBase.h"
#include "OmokNode.generated.h"

UCLASS()
class OMOK_API AOmokNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOmokNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetNodeColor(ENodeColor NewColor);

	UFUNCTION()
	void ReactOnBeginCursorOverlap();
	
	UFUNCTION()
	void ReactOnEndCursorOverlap();

	UFUNCTION()
	void ReactOnClick();

	FORCEINLINE ENodeColor GetNodeColor() const { return CurrentColor; }

	void SetMaterials(const TArray<TObjectPtr<UMaterial>>& NodeMaterials);

	void SetCoordinate(int32 X, int32 Y);

	FORCEINLINE const FIntVector2& GetCoordinate() const { return Coordinate; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> NodeMesh;

	//검은색.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> BlackMaterial;	
	
	//반투명 검은색.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> ClearBlackMaterial;	

	//흰색.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> WhiteMaterial;	
	
	//반투명 흰색.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> ClearWhiteMaterial;	
	
	//투명(진짜 투명이면 안보여서 실제로는 반투명 파란색).
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterial> ClearMaterial;	

	//게임스테이트.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AOmokGameStateBase> OmokGameState;

private:
	FScriptDelegate BeginCursorOverlapDelegate;
	FScriptDelegate EndCursorOverlapDelegate;
	FScriptDelegate ClickDelegate;

	ENodeColor CurrentColor;	//현재 노드 색상.
	bool IsFixed;	//노드 색상 고정 됨/안됨.
	FIntVector2 Coordinate;	//노드 좌표. X++이 위, Y++이 오른쪽.
};
