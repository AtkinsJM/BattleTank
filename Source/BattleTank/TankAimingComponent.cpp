// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((LastFireTime + FireDelay) > (GetWorld()->GetTimeSeconds()))
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	FString TankName = GetOwner()->GetName();
	FVector LaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHasLaunchVelocity = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHasLaunchVelocity)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		//TODO call IsBarrelMoving method here instead?
		if (IsBarrelMoving())
		{
			MoveBarrel(AimDirection);
			MoveTurret(AimDirection);
		}
	}
}

void UTankAimingComponent::MoveBarrel(FVector LaunchDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator LaunchRotator = LaunchDirection.Rotation();
	FRotator DeltaRotator = LaunchRotator - BarrelRotator;
	float Direction = (DeltaRotator.Pitch / abs(DeltaRotator.Pitch));
	Barrel->Elevate(Direction);
}

void UTankAimingComponent::MoveTurret(FVector LaunchDirection)
{
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator LaunchRotator = LaunchDirection.Rotation();
	FRotator DeltaRotator = LaunchRotator - TurretRotator;
	float Direction = (DeltaRotator.Yaw / abs(DeltaRotator.Yaw));
	Turret->Turn(Direction);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	if (Barrel->GetForwardVector().Equals(AimDirection, AimTolerance))
	{
		return false;
	}
	return true;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }
	if (FiringState != EFiringState::Reloading)
	{
		//Spawn projectile at barrel socket
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketTransform(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	};
}