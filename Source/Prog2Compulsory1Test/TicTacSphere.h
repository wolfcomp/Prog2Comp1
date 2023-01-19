// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TicTacSphere.generated.h"

UCLASS()
class PROG2COMPULSORY1TEST_API ATicTacSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATicTacSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
public:
	void SetColor(FVector4 NewColor);
	bool bIsLocked = false;
};
