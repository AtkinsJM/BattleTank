// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FString TankName = GetOwner()->GetName();
	if (!Barrel)
	{
		return;
	}
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
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *TankName, *LaunchDirection.ToString(), *(Barrel->GetComponentLocation().ToString()));
	}

}


void UTankAimingComponent::MoveBarrel(FVector LaunchDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator LaunchRotator = LaunchDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("Barrel rotator: %s, Launch rotator: %s"), *BarrelRotator.ToString(), *LaunchRotator.ToString());
	FRotator DeltaRotator = LaunchRotator - BarrelRotator;
	float Direction = (DeltaRotator.Pitch / abs(DeltaRotator.Pitch));
	Barrel->Elevate(Direction);
}

void UTankAimingComponent::MoveTurret(FVector LaunchDirection)
{
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator LaunchRotator = LaunchDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("Turret rotator: %s, Launch rotator: %s"), *TurretRotator.ToString(), *LaunchRotator.ToString());
	FRotator DeltaRotator = LaunchRotator - TurretRotator;
	float Direction = (DeltaRotator.Yaw / abs(DeltaRotator.Yaw));
	Turret->Turn(Direction);
}