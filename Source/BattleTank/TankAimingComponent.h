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
	void AimAt(FVector HitLocation, float LaunchSpeed);
	UTankBarrel* Barrel = nullptr;

private:
	UTankTurret* Turret = nullptr;
	
	void MoveBarrel(FVector LaunchDirection);
	void MoveTurret(FVector LaunchDirection);
};
