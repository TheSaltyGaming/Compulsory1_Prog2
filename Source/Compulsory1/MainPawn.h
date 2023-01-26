// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "GameFramework/Pawn.h"
#include "MainPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UMaterial;

UCLASS()
class COMPULSORY1_API AMainPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	bool RedTurn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* White;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category= "Arrays")
	TArray<UStaticMeshComponent*> MeshArray;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	int TurnCounter = 0;
	TArray<int> SphereStatus;
	
	void OnePressed();
	void TwoPressed();
	void ThreePressed();
	void FourPressed();
	void FivePressed();
	void SixPressed();
	void SevenPressed();
	void EightPressed();
	void NinePressed();

	void TurnController(int SphereIndex);

	void SetSphereLocation();

	void WinCheck();

// put more stuff here

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeColor();

};
