// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declarations
class UTankAimingComponent;
class ATank;
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
	UPROPERTY(EditAnywhere, Category = "Firing")
		float AcceptanceRadius = 7000.0f;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ATank* AITank;
	ATank* PlayerTank;
	UTankAimingComponent* TankAimingComponent = nullptr;

	UFUNCTION()
		void OnTankDeath();
	
};
