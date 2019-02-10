// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 7000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP;

	//UTankBarrel* Barrel = nullptr;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float FireDelay = 5;
};
