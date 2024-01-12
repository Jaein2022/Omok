// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmokPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OMOK_API AOmokPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend class UOmokLobbyUI;
	friend class UOmokHostingUI;

public:
	AOmokPlayerController();

	

	FORCEINLINE void SetColor(const bool InbWhite) { this->bWhite = InbWhite; }
	FORCEINLINE bool GetColor() const { return bWhite; }


protected:
	virtual void BeginPlay() override;

private:
	void StartHosting() const;

	void CancelHosting();
	
	void ConnectToIPAddress(const FText& IPAddress);

	void Disconnect();

	void QuitGame();


private:
	TSubclassOf<class UUserWidget> LobbyUIClass;
	TObjectPtr<class UOmokLobbyUI> LobbyUI;

	TSubclassOf<class UUserWidget> HostingUIClass;
	TObjectPtr<class UOmokHostingUI> HostingUI;

	bool bWhite;

};
