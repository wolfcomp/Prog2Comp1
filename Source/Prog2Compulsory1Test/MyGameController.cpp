// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameController.h"
#include "TicTacSphere.h"
#include "Kismet/GameplayStatics.h"

//function to find all actors of a class
void AMyGameController::GetAllTicTacSpheres(int32 Index)
{
	if(bGamePlaying)
	{
		TArray<AActor*> ActorsToFind;
		FString a = "sphere ";
		a.AppendInt(Index);
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATicTacSphere::StaticClass(), FName(*a), ActorsToFind);
		ATicTacSphere* TicTacSphere = Cast<ATicTacSphere>(ActorsToFind[0]);

		if (!TicTacSphere->bIsLocked)
		{
			if (TicTacSphere)
			{
				if (bIsPlayer1Turn)
				{
					TicTacSphere->SetColor(FVector4(0, 0, 1, 1));
					gamestate[Index] = 1;
				}
				else
				{
					TicTacSphere->SetColor(FVector4(1, 0, 0, 1));
					gamestate[Index] = 2;
				}
			}
			bIsPlayer1Turn = !bIsPlayer1Turn;
			//check for win condition here
			for (int i = 1; i <=2; i++)
			{
				if(
					(gamestate[0] == i && gamestate[4] == i && gamestate[8] == i) ||
					(gamestate[2] == i && gamestate[4] == i && gamestate[6] == i) ||
					(gamestate[0] == i && gamestate[1] == i && gamestate[2] == i) ||
					(gamestate[3] == i && gamestate[4] == i && gamestate[5] == i) ||
					(gamestate[6] == i && gamestate[7] == i && gamestate[8] == i) ||
					(gamestate[0] == i && gamestate[3] == i && gamestate[6] == i) ||
					(gamestate[1] == i && gamestate[4] == i && gamestate[7] == i) ||
					(gamestate[2] == i && gamestate[5] == i && gamestate[8] == i))
				{
					if (!bIsPlayer1Turn)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("p1wins"));
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("p2wins"));
					}
					bGamePlaying = false;
				}
			}
		}
	}
}

void AMyGameController::DeclareWinner(int i)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("declare winner fired"));
	if (i == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("p1wins"));
	}
	if (i == 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("p2wins"));
	}
	bGamePlaying = false;
}

// Sets default values
AMyGameController::AMyGameController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyGameController::BeginPlay()
{
	Super::BeginPlay();
	//start code taken and modified from https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/HowTo/FindingActors/
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATicTacSphere::StaticClass(), ActorsToFind);
	}
	//end code taken

	for (AActor* TicTacSphereActor : ActorsToFind)
	{
		ATicTacSphere* TicTacSphereCast = Cast<ATicTacSphere>(TicTacSphereActor);
		if (TicTacSphereCast)
		{
			GameSpheres.Add(TicTacSphereCast);
		}
	}
}

// Called every frame
void AMyGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyGameController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//taken and modified from here: https://forums.unrealengine.com/t/bindaction-delegate-with-parameters/301095/3

	PlayerInputComponent->BindAction<MyDelegate>("Select1", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 0);
	PlayerInputComponent->BindAction<MyDelegate>("Select2", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 1);
	PlayerInputComponent->BindAction<MyDelegate>("Select3", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 2);
	PlayerInputComponent->BindAction<MyDelegate>("Select4", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 3);
	PlayerInputComponent->BindAction<MyDelegate>("Select5", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 4);
	PlayerInputComponent->BindAction<MyDelegate>("Select6", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 5);
	PlayerInputComponent->BindAction<MyDelegate>("Select7", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 6);
	PlayerInputComponent->BindAction<MyDelegate>("Select8", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 7);
	PlayerInputComponent->BindAction<MyDelegate>("Select9", IE_Pressed, this, &AMyGameController::GetAllTicTacSpheres, 8);

}


