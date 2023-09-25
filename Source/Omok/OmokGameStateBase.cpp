// Fill out your copyright notice in the Description page of Project Settings.


#include "OmokGameStateBase.h"
#include "Board/OmokBoard.h"

AOmokGameStateBase::AOmokGameStateBase()
{
}

void AOmokGameStateBase::CreateOmokBoard_Implementation(const FVector& BoardLocation)
{
	const FString CurrentMapName = GetWorld()->GetMapName().RightChop(GetWorld()->StreamingLevelsPrefix.Len());
	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, CurrentMapName);

	ensure(TEXT("PlayMap") == CurrentMapName);
	//이 함수는 플레이맵에서만 호출해야하는 함수.

	this->OmokBoard = GetWorld()->SpawnActor<AOmokBoard>();
	this->OmokBoard->SetActorLocation(BoardLocation);

}
