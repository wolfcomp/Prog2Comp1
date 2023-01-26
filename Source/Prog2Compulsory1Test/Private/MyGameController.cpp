// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameController.h"
#include "TicTacSphere.h"

//function to find all actors of a class
void AMyGameController::GetAllTicTacSpheres(int32 Index)
{
	if (bGamePlaying)
	{
		ATicTacSphere* TicTacSphere = SphereArray[Index];

		if (!TicTacSphere->bIsLocked)
		{
			if (TicTacSphere)
			{
				if (bIsPlayer1Turn)
				{
					TicTacSphere->SetColor(FVector4(0, 0, 1, 1));
					GameState[Index] = 1;
				}
				else
				{
					TicTacSphere->SetColor(FVector4(1, 0, 0, 1));
					GameState[Index] = 2;
				}
			}
			bIsPlayer1Turn = !bIsPlayer1Turn;
			//check for win condition here
			for (int i = 1; i <= 2; i++)
			{
				bool bWin = false;
				for (int j = 0; j < 3; ++j)
				{
					if (GameState[j] == i && GameState[j + 3] == i && GameState[j + 6] == i)
					{
						bWin = true;
					}
					if (GameState[j * 3] == i && GameState[j * 3 + 1] == i && GameState[j * 3 + 2] == i)
					{
						bWin = true;
					}
				}
				if ((GameState[0] == i && GameState[4] == i && GameState[8] == i)
					||
					(GameState[2] == i && GameState[4] == i && GameState[6] == i))
				{
					bWin = true;
				}
				if (bWin)
				{
					DeclareWinner(i);
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

void AMyGameController::ClientSetPlayerId_Implementation(int32 Id)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("client set player id fired"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(Id));
}

// Sets default values
AMyGameController::AMyGameController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshFinder(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	this->SphereMesh = SphereMeshFinder.Object;

	const ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("Material'/Game/NewMaterial.NewMaterial'"));
	this->Material = MaterialFinder.Object;

	SphereArray.Init(nullptr, 9);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 800));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyGameController::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float x = (i - 1) * SphereDistance;
			float y = (j - 1) * SphereDistance;
			auto sphere = GetWorld()->SpawnActor<ATicTacSphere>(FVector(x, y, 0), FRotator(0, 0, 0));
			sphere->SetMesh(SphereMesh);
			sphere->SetRadius(SphereRadius);
			sphere->SetMaterial(Material);
			sphere->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
			SphereArray[i * 3 + j] = sphere;
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


