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

	//InbWhite 색상의 플레이어가 승리 조건을 달성했는지 확인하는 함수. 서버 전용.
	bool CheckWinningCondition(const FIntVector2& InCoord, const uint8 InbWhite) const;
	//로직 변경 예정.
	
	/**
	* 주어진 좌표의 돌부터 같은 색의 바둑알이 연속으로 몇개나 있는지 세는 함수.
	* @param X: 바둑알 X좌표.
	* @param Y: 바둑알 Y좌표.
	* @param InbWhite: 바둑알의 색상.
	* @param XDir: 1: 위쪽, -1: 아래쪽. 1, 0, -1만 입력할 것.
	* @param YDir: 1: 오른쪽, -1: 왼쪽. 1, 0, -1만 입력할 것.
	*/
	const int32 CountSameColorNodes(const int32 X, const int32 Y, const uint8 InbWhite, const int8 XDir, const int8 YDir) const;

public:
	virtual void OnRep_PlayerState() override;



public:
	FORCEINLINE TObjectPtr<class AOmokBoard> GetBoard() const { return OmokBoard; } 



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> OmokPlayerCamera;



private:
	UFUNCTION()
	void OnBeginCursorOver_SetClearColor(AActor* TouchedActor);

	UFUNCTION()
	void OnEndCursorOver_ReturnColor(AActor* TouchedActor);

	UFUNCTION()
	void OnClicked_FixColor(AActor* ClickedActor, const FKey PressedButton);



private:
	const FVector2D BoardLocationFromPlayer = { 200, 100 };	//플레이어 위치 기준 바둑판 배치 위치.

	const int32 WinningCount = 5;	//이기기 위해 연속으로 놓여야 하는 돌의 개수.

	TObjectPtr<class AOmokBoard> OmokBoard;	//바둑판.

	TObjectPtr<class AOmokPlayerState> OmokPlayerState;
};
