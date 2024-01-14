// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmokPlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnConnectedAsClient);
DECLARE_MULTICAST_DELEGATE(FOnDisconnected);

/**
 * 
 */
UCLASS()
class OMOK_API AOmokPlayerController : public APlayerController
{
	GENERATED_BODY()

	//

public:
	AOmokPlayerController();

	

	FORCEINLINE void SetColor(const bool InbWhite) { this->bWhite = InbWhite; }
	FORCEINLINE bool GetColor() const { return bWhite; }



protected:
	virtual void BeginPlay() override;



private:
	//호스팅 시작 함수.
	UFUNCTION()
	void StartHosting();	

	//호스팅 취소 함수.
	UFUNCTION()
	void CancelHosting();
	
	//입력받은 IP 주소의 호스팅에 클라이언트로 접속하는 함수. 
	UFUNCTION()
	void ConnectToIPAddress();	

	//클라이언트의 연결 해제 함수.
	UFUNCTION()
	void Disconnect();

	//게임 완전 종료 함수.
	UFUNCTION()
	void QuitGame();



private:
	TSubclassOf<class UUserWidget> LobbyUIClass;
	TObjectPtr<class UOmokLobbyUI> LobbyUI;

	TSubclassOf<class UUserWidget> HostingUIClass;
	TObjectPtr<class UOmokHostingUI> HostingUI;

	bool bWhite;
};
