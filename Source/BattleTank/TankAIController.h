// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declarations
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AActor* AITank;
	AActor* PlayerTank;
	UTankAimingComponent* TankAimingComponent = nullptr;

	float AcceptanceRadius = 2000.0f;
};
