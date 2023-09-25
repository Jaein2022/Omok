// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OmokGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API AOmokGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AOmokGameStateBase();
	//GameState Base가 아니라 GameState를 상속받아서 커스텀 GameState를 만들면,
	// 레벨 블루프린트의 BeginPlay 이벤트가 제대로 호출되지 않는다.

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void CreateOmokBoard(const FVector& BoardLocation);
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AOmokBoard> OmokBoard;


};
