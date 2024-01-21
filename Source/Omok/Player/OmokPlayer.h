// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OmokPlayer.generated.h"

//플레이어.
UCLASS()
class OMOK_API AOmokPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOmokPlayer(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	FORCEINLINE TObjectPtr<class AOmokBoard> GetBoard() const { return Board; } 



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> OmokPlayerCamera;

	TObjectPtr<class AOmokBoard> Board;	//바둑판.



private:
	UFUNCTION()
	void OnBeginCursorOver_SetClearColor(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndCursorOver_ReturnColor(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnClicked_FixColor(UPrimitiveComponent* ClickedComponent, const FKey PressedButton);



private:
	const FVector2D BoardLocationFromPlayer;	//바둑판 배치 위치.


};
