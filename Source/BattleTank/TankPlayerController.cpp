// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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
	FVector OutHitLocation; //Out parameter
	if (GetAimRayHitLocation(OUT OutHitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *OutHitLocation.ToString());
		//TODO Aim barrel at point
	}
}

bool ATankPlayerController::GetAimRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	//Get screen position of crosshair
	FVector2D ScreenPosition = FVector2D(ViewportSizeX * CrosshairPosX, ViewportSizeY * CrosshairPosY);
	//Deproject screen position to world
	//Linetrace along look direction and get hit

	return true;
}
