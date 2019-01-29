// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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
	if (!GetPlayerTank) 
	{
		return;
	}
	//Get world location of linetrace from UI crosshair
	//If linetrace hits something
		//Aim barrel at point
}
