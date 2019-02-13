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
	Reloading,
	OutOfAmmo
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
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetRoundsLeft() const;

	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP;
	UTankBarrel* Barrel = nullptr;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 7000.0f;

	UTankTurret* Turret = nullptr;
	
	void MoveBarrelAndTurret(FRotator LaunchRotator);

	bool IsBarrelRotating();
	FVector AimDirection = FVector(0);
	float AimTolerance = 0.01f;
	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxPitch = 35.0f;	//Degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinPitch = 0.0f;	//Degrees

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float FireDelay = 5;

	int RoundsLeft = 5;
};
