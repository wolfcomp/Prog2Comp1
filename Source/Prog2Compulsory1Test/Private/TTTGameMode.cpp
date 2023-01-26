// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTGameMode.h"

#include "MyGameController.h"
#include "Kismet/GameplayStatics.h"

void ATTTGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	if(!NewPlayer->GetPawn())
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Player Joined"));

	if(APawn* TmpPawn = NewPlayer->GetPawn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TmpPawn->GetHumanReadableName());
		TmpPawn->Destroy();
	}

	FTransform SpawnTransform = FTransform();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyGameController::StaticClass(), FoundActors);

	if(FoundActors.Num() > 0)
	{
		SpawnTransform = FoundActors.Last()->GetActorTransform();
		UE::Math::TVector Location = SpawnTransform.GetLocation();
		Location.X += 4000;
		SpawnTransform.SetLocation(Location);
	}

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = NewPlayer;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector TmpLoc = SpawnTransform.GetLocation();
	const FRotator TmpRot = SpawnTransform.GetRotation().Rotator();
	AMyGameController* NewController = Cast<AMyGameController>(GetWorld()->SpawnActor(AMyGameController::StaticClass(), &TmpLoc, &TmpRot, SpawnInfo));
	NewPlayer->Possess(NewController);
}
