// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacSphere.h"

// Sets default values
ATicTacSphere::ATicTacSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	CollisionEnabledIntersection(ECollisionEnabled::NoCollision, ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATicTacSphere::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATicTacSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void ATicTacSphere::SetMaterial(UMaterialInterface* NewMaterial)
{
	DynamicMaterial = UMaterialInstanceDynamic::Create(NewMaterial, nullptr);
	Mesh->SetMaterial(0, DynamicMaterial);
}

void ATicTacSphere::SetRadius(float NewRadius)
{
	Mesh->SetWorldScale3D(FVector(NewRadius));
}

void ATicTacSphere::SetMesh(UStaticMesh* NewMesh)
{
	Mesh->SetStaticMesh(NewMesh);
}