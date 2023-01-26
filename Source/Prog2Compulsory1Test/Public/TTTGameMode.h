// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TTTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROG2COMPULSORY1TEST_API ATTTGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
