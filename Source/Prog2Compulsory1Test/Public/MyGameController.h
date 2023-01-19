// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacSphere.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	UPROPERTY(EditAnywhere)
		TArray<ATicTacSphere*> SphereArray;
	int GameState[9] = { 0,0,0,0,0,0,0,0,0 };

	UPROPERTY(EditAnywhere)
		float SphereRadius = 100.0f;
	UPROPERTY(EditAnywhere)
		float SphereDistance = 200.0f;
	UPROPERTY(EditAnywhere)
		UMaterial* Material;
	UPROPERTY(EditAnywhere)
		UStaticMesh* SphereMesh;
protected:
	void GetAllTicTacSpheres(int32 Index);

	void DeclareWinner(int i);

	DECLARE_DELEGATE_OneParam(MyDelegate, int32);

	bool bIsPlayer1Turn = true;

	bool bGamePlaying = true;

	int playerId;

	UFUNCTION(Client, Reliable)
		void ClientSetPlayerId(int32 Id);

	UStaticMeshComponent* Mesh;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere)
		USpringArmComponent* SpringArm;

	UCameraComponent* Camera;
};
