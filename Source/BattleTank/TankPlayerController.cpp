// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed tank: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No possessed tank"));
	}
}

ATank* ATankPlayerController::GetPlayerTank() const
{	
	return(Cast<ATank>(GetPawn()));
}