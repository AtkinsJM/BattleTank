// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Aiming state Enum
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

//Forward declarations
class UTankBarrel;	
class UTankTurret;
class AProjectile;

//Holds properties of tank barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable)
		void Fire();
	void AimAt(FVector HitLocation);
	UTankBarrel* Barrel = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 7000.0f;

	UTankTurret* Turret = nullptr;
	
	void MoveBarrel(FVector LaunchDirection);
	void MoveTurret(FVector LaunchDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float FireDelay = 5;
};
