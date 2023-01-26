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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere,Category="TickTackToe")
	AGameManager* GameManager;

	UPROPERTY(EditAnywhere, Category = "TickTackToe")
	EPlayer CurrentPlayer;

// put more stuff here

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeColor();

};
