// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UENUM(BlueprintType)
enum class EPlayer : uint8
{
	None,
	X,
	O
};


UCLASS()
class COMPULSORY1_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickTackToe")
	class AMainPawn* Pawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
