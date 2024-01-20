// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmokPlayerController.generated.h"

/**
 * 서버 접속 관리 및 UI 입력처리 클래스.
 */
UCLASS()
class OMOK_API AOmokPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOmokPlayerController();

	//클라이언트의 Ready 버튼을 깜빡거리게 하는 함수.
	UFUNCTION(Client, Unreliable)
	void ClientRPC_FlickerReadyButton();

	//Ready 버튼을 깜빡거리게 하는 함수.
	void FlickerReadyButton();

	void ReceiveMessage(const FText& InText, const uint8 SenderColor);

	void SetMessageColor(const uint8 InbWhite);



public:
	FORCEINLINE void SetbWhite(const uint8 InbWhite) { bWhite = InbWhite; }
	FORCEINLINE const uint8 GetbWhite() const { return bWhite; }



protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



private:
	//호스팅 시작 함수.
	UFUNCTION()
	void StartHosting();	

	//호스팅 취소 함수.
	UFUNCTION()
	void CancelHosting();
	
	//Enter 버튼을 눌렀을때 입력받은 IP 주소의 호스트에 클라이언트로 접속하는 함수. 
	UFUNCTION()
	void OnClickedEnterButton_Connect();	

	//엔터키를 눌렀을 때 입력된 IP 주소의 호스트에 클라이언트로 접속하는 함수. 
	UFUNCTION()
	void OnTextCommitted_Connect(const FText& InText, ETextCommit::Type CommitMethod);

	//클라이언트의 연결 해제 함수.
	UFUNCTION()
	void Disconnect();

	//Ready 버튼 눌렀을때 호출되는 함수.
	UFUNCTION()
	void OnClickedReadyButton();

	//게임 완전 종료 함수.
	UFUNCTION()
	void QuitGame();

	//클라이언트가 Ready 버튼을 눌렀다고 서버에게 알리는 함수.
	UFUNCTION(Server, Unreliable)
	void ServerRPC_NotifyOnReadied();

	UFUNCTION()
	void OnTextCommitted_SendMessage(const FText& InText, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnClickedSendButton_SendMessage();



private:
	TSubclassOf<class UUserWidget> LobbyUIClass;
	TObjectPtr<class UOmokLobbyUI> LobbyUI;

	TSubclassOf<class UUserWidget> HostingUIClass;
	TObjectPtr<class UOmokHostingUI> HostingUI;

	TSubclassOf<class UUserWidget> PlayUIClass;
	TObjectPtr<class UOmokPlayUI> PlayUI;



private:
	UPROPERTY(ReplicatedUsing = OnRep_bWhite)
	uint8 bWhite:1;

	UFUNCTION()
	void OnRep_bWhite();
};
