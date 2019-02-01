// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

#define OUT

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player possessed tank: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No player possessed tank"));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetPlayerTank() const
{	
	return(Cast<ATank>(GetPawn()));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPlayerTank()) {	return;	}
	FVector HitLocation; //Out parameter
	if (GetAimRayHitLocation(OUT HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
		//TODO Aim barrel at point
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
		if (GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Visibility))
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
