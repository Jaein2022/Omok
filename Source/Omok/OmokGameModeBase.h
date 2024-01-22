// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmokGameModeBase.generated.h"

//
UCLASS()
class OMOK_API AOmokGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	


public:
	AOmokGameModeBase();

	virtual APlayerController* Login(
		UPlayer* NewPlayer,
		ENetRole InRemoteRole,
		const FString& Portal,
		const FString& Options,
		const FUniqueNetIdRepl& UniqueId,
		FString& ErroMessage
	) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void SetServerReady(const TObjectPtr<class AOmokPlayerController> ThisOmokPC);

	void SetClientReady(const TObjectPtr<class AOmokPlayerController> ThisOmokPC);

	void BroadcastWinner(const TObjectPtr<class APlayerController> Winner);



private:
	const int32 PlayerLimit = 2;	//플레이어 숫자 제한.
	bool bServerReady;
	bool bClientReady;
	uint8 bWhite_Initialization: 1;	//새로 로그인하는 플레이어에게 부여할 색상.
};
