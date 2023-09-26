// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmokNode.generated.h"

UENUM()
enum class ENodeColor: uint8
{
	Black,
	ClearBlack,
	White,
	ClearWhite,
	Clear
};

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

	FORCEINLINE ENodeColor GetNodeColor() { return CurrentColor; }

	void SetMaterials(const TArray<TObjectPtr<UMaterial>>& NodeMaterials);


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
	TObjectPtr<UMaterial> ClearMaterial;

	ENodeColor CurrentColor;	//현재 색상.
	bool IsFixed;	//색상 고정 됨/안됨.

	FScriptDelegate BeginCursorOverlapDelegate;
	FScriptDelegate EndCursorOverlapDelegate;
	FScriptDelegate ClickDelegate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class AOmokGameStateBase> OmokGameState;

};
