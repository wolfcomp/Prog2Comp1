// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacSphere.h"
#include "MyGameController.generated.h"

UCLASS()
class PROG2COMPULSORY1TEST_API AMyGameController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyGameController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	TArray<ATicTacSphere*> GameSpheres;
	int gamestate[9] = {0,0,0,0,0,0,0,0,0};
protected:
		void GetAllTicTacSpheres(int32 Index);
		void DeclareWinner(int i);
		DECLARE_DELEGATE_OneParam(MyDelegate, int32);
		bool bIsPlayer1Turn = true;
		bool bGamePlaying = true;
};
