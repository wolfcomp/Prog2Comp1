// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacSphere.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ATicTacSphere::ATicTacSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATicTacSphere::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("TicTacTag"));

	auto Sphere = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Sphere->GetMaterial(0);

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Sphere->SetMaterial(0, DynamicMaterial);
}

// Called every frame
void ATicTacSphere::Tick(float DeltaTime)
{

}

//set color function
void ATicTacSphere::SetColor(FVector4 NewColor)
{
	if(!bIsLocked)
	{
		//GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Yellow, TEXT("SetColor was called"));
		bIsLocked = true;
		DynamicMaterial->SetVectorParameterValue(TEXT("Color"), NewColor);
	}
}

