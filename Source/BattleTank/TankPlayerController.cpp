// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

#define OUT

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<ATank>(GetPawn());
	if (!PlayerTank) { return; }
	TankAimingComponent = PlayerTank->FindComponentByClass<UTankAimingComponent>();
	PlayerTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsActive)
	{
		AimTowardsCrosshair();
	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!TankAimingComponent) {	return;	}
	FVector HitLocation; //Out parameter
	if (GetAimRayHitLocation(OUT HitLocation))
	{
		//Aim barrel at point
		TankAimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetAimRayHitLocation(OUT FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	//Get screen position of crosshair
	FVector2D ScreenPosition = FVector2D(ViewportSizeX * CrosshairPosX, ViewportSizeY * CrosshairPosY);
	FVector LineStart;
	FVector LookDirection; 
	//Deproject screen position to world and get world location and look direction for ray
	if (DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, OUT LineStart, OUT LookDirection))
	{
		//Linetrace along look direction and get hit
		FHitResult HitResult;
		FVector LineEnd = LineStart + (LookDirection * LineTraceRange);
		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(PlayerTank);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Camera, CollisionParameters))
		{
			HitLocation = HitResult.Location;
			return true;
		}
		HitLocation = FVector(0);
		return false;
	};
	UE_LOG(LogTemp, Warning, TEXT("Unable to deproject screen position to world."));
	return false;
}

void ATankPlayerController::OnTankDeath()
{
	bIsActive = false;
	StartSpectatingOnly();
	
}