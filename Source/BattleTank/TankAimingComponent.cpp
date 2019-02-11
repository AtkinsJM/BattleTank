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
	//Assigns ProbjectileBP class (to avoid blueprint assign breaking on recompile
	//TODO find alternate way of doing this
	static ConstructorHelpers::FClassFinder<AProjectile> Proj(TEXT("/Game/Tank/Projectile_BP"));
	if (Proj.Class)
	{
		ProjectileBP = Proj.Class;
	}
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
		FVector LaunchDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(LaunchDirection);
		MoveTurret(LaunchDirection);
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

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }
	bool bCanFire = (LastFireTime + FireDelay) < (GetWorld()->GetTimeSeconds());
	if (bCanFire)
	{
		//Spawn projectile at barrel socket
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketTransform(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	};
}