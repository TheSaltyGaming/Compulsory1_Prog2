// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainPawn::AMainPawn()
{
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshArray.Init(NULL,9);
	LightArray.Init(NULL, 3);

	
	for (int i = 0; i < 9; i++)
	{
		MeshArray[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh" + FString::FromInt(i)));
		//GEngine->AddOnScreenDebugMessage(-1, 10 , FColor::Red, FString::FromInt(i));
	}

	RootComponent = MeshArray[4];
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	for (int i = 0; i < 9; i++)
	{
		if (i != 4)
		{
			MeshArray[i]->SetupAttachment(GetRootComponent());
		}
		MeshArray[i]->SetStaticMesh(MeshComponentAsset.Object);
		//GEngine->AddOnScreenDebugMessage(-1, 10 , FColor::Red, FString::FromInt(i));
	}
	for (int i = 0; i < LightArray.Num(); i++)
	{
		LightArray[i] = CreateDefaultSubobject<USpotLightComponent>(FName("SpotLight" + FString::FromInt(i)));
	}

	
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	
	SphereStatus.Init(NULL,9);

	

	SetSphereLocation();

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 9; i++)
	{
		MeshArray[i]->SetMaterial(0, White);
	}
	
}



// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (int i = 0; i <LightArray.Num(); i++)
	{
		if (LightArray[i] != NULL && TurnCounter % 2 == 0)
		{
			LightArray[0]->SetLightColor(FColor::Red);
			LightArray[1]->SetLightColor(FColor::Red);
			LightArray[2]->SetLightColor(FColor::Red);
			
		}
		else if (LightArray[i] != NULL && TurnCounter % 2 == 1)
		{
			LightArray[0]->SetLightColor(FColor::Blue);
			LightArray[1]->SetLightColor(FColor::Blue);
			LightArray[2]->SetLightColor(FColor::Blue);
		}
	}
}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("OnePressed", IE_Pressed, this, &AMainPawn::OnePressed);
	PlayerInputComponent->BindAction("TwoPressed", IE_Pressed, this, &AMainPawn::TwoPressed);
	PlayerInputComponent->BindAction("ThreePressed", IE_Pressed, this, &AMainPawn::ThreePressed);
	PlayerInputComponent->BindAction("FourPressed", IE_Pressed, this, &AMainPawn::FourPressed);
	PlayerInputComponent->BindAction("FivePressed", IE_Pressed, this, &AMainPawn::FivePressed);
	PlayerInputComponent->BindAction("SixPressed", IE_Pressed, this, &AMainPawn::SixPressed);
	PlayerInputComponent->BindAction("SevenPressed", IE_Pressed, this, &AMainPawn::SevenPressed);
	PlayerInputComponent->BindAction("EightPressed", IE_Pressed, this, &AMainPawn::EightPressed);
	PlayerInputComponent->BindAction("NinePressed", IE_Pressed, this, &AMainPawn::NinePressed);

}

void AMainPawn::TurnController(int SphereIndex)
{
	if (gameOver) return;
	
	UE_LOG(LogTemp, Warning, TEXT("SphereIndex: %d"), SphereIndex);
	if (SphereStatus[SphereIndex] != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sphere is already taken"));
		return;
	}
	if (TurnCounter % 2 == 0)
	{
		MeshArray[SphereIndex]->SetMaterial(0,Red);
		SphereStatus [SphereIndex] = 1;
	}
	else
	{
		MeshArray[SphereIndex]->SetMaterial(0,Blue);
		SphereStatus [SphereIndex] = 2;
	}
	TurnCounter++;

	WinCheck();
}

void AMainPawn::WinCheck()
{
	//Checks vertical win condition
	for (int i = 0; i < 3; i++)
	{
		if (SphereStatus[i] == 1 && SphereStatus[i+3] == 1 && SphereStatus[i+6] == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Red win vertical"));
			GEngine->AddOnScreenDebugMessage(1,60,FColor::Red,TEXT("Red Wins"));
			gameOver = true;
			TurnCounter++;
		}
		if (SphereStatus[i] == 2 && SphereStatus[i+3] == 2 && SphereStatus[i+6] == 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Blue win vertical"));
			GEngine->AddOnScreenDebugMessage(1,60,FColor::Blue,TEXT("Blue Wins"));
			gameOver = true;
			TurnCounter++;
		}
	}
	//Checks horizontal win condition
	for (int i = 0; i<9; i+=3)
	{
		if (SphereStatus[i] == 1 && SphereStatus[i+1] == 1 && SphereStatus[i+2] == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Red win Horizontal"));
			gameOver = true;
			TurnCounter++;
			GEngine->AddOnScreenDebugMessage(1,60,FColor::Red,TEXT("Red Wins"));
		}
		if (SphereStatus[i] == 2 && SphereStatus[i+1] == 2 && SphereStatus[i+2] == 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Blue win Horizontal"));
			gameOver = true;
			TurnCounter++;
			GEngine->AddOnScreenDebugMessage(1,60,FColor::Blue,TEXT("Blue Wins"));
		}
	}
#pragma region DiagonalWinCheck
	if (SphereStatus[0] == 1 && SphereStatus[4] == 1 && SphereStatus[8] == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Red win diagonal"));
		gameOver = true;
		TurnCounter++;
		GEngine->AddOnScreenDebugMessage(1,60,FColor::Red,TEXT("Red Wins"));
	}
	if (SphereStatus[0] == 2 && SphereStatus[4] == 2 && SphereStatus[8] == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blue win diagonal"));
		gameOver = true;
		TurnCounter++;
		GEngine->AddOnScreenDebugMessage(1,60,FColor::Blue,TEXT("Blue Wins"));
	}
	if (SphereStatus[2] == 1 && SphereStatus[4] == 1 && SphereStatus[6] == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Red win diagonal"));
		gameOver = true;
		TurnCounter++;
		GEngine->AddOnScreenDebugMessage(1,60,FColor::Blue,TEXT("Red Wins"));
	}
	if (SphereStatus[2] == 2 && SphereStatus[4] == 2 && SphereStatus[6] == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blue win diagonal"));
		gameOver = true;
		TurnCounter++;
		GEngine->AddOnScreenDebugMessage(1,60,FColor::Red,TEXT("Blue Wins"));
	}
#pragma endregion 
}


void AMainPawn::SetSphereLocation()
{
	MeshArray[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	MeshArray[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	MeshArray[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	MeshArray[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	MeshArray[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	MeshArray[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	MeshArray[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	MeshArray[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	MeshArray[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));
}


void AMainPawn::OnePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("OnePressed"));
	TurnController(0);
}

void AMainPawn::TwoPressed()
{
	TurnController(1);
}

void AMainPawn::ThreePressed()
{
	TurnController(2);
}

void AMainPawn::FourPressed()
{
	TurnController(3);
}

void AMainPawn::FivePressed()
{
	TurnController(4);
}

void AMainPawn::SixPressed()
{
	TurnController(5);
}

void AMainPawn::SevenPressed()
{
	TurnController(6);
}

void AMainPawn::EightPressed()
{
	TurnController(7);
}

void AMainPawn::NinePressed()
{
	TurnController(8);
}


