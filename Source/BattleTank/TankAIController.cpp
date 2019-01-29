// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* AITank = GetAITank();
	if (AITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI possessed tank: %s"), *(AITank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI possessed tank"));
	}
}

ATank* ATankAIController::GetAITank() const
{
	return(Cast<ATank>(GetPawn()));
}
