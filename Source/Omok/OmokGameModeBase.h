// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmokGameModeBase.generated.h"

/**
 * 
 */
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

	void SetServerReady(TObjectPtr<class AOmokPlayerController> InOmokPC);
	void SetClientReady(TObjectPtr<class AOmokPlayerController> InOmokPC);



protected:



private:
	bool bServerReady;
	bool bClientReady;
	bool bWhite;
};
