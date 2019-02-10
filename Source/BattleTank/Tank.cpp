// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool bCanFire = (LastFireTime + FireDelay) < (GetWorld()->GetTimeSeconds());
	if (TankAimingComponent->Barrel && bCanFire)
	{
		//Spawn projectile at barrel socket
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, TankAimingComponent->Barrel->GetSocketTransform(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	};
}
