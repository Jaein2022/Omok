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

	void SetServerReady(const TObjectPtr<class AOmokPlayerController> ThisOmokPC);

	void SetClientReady(const TObjectPtr<class AOmokPlayerController> ThisOmokPC);

	void BroadcastMatchEnd(const TObjectPtr<class APlayerController> Winner);



public:
	virtual APlayerController* Login(
		UPlayer* NewPlayer,
		ENetRole InRemoteRole,
		const FString& Portal,
		const FString& Options,
		const FUniqueNetIdRepl& UniqueId,
		FString& ErroMessage
	) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;



private:
	const int32 PlayerLimit = 2;	//플레이어 숫자 제한.
	bool bServerReady;
	bool bClientReady;
	uint8 bWhiteForNewPlayer: 1;	//새로 로그인하는 플레이어에게 부여할 색상.
};
