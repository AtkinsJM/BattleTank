// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s found player tank %s"), *(AITank->GetName()), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s did not find player tank."), *(AITank->GetName()));
	}
}

ATank* ATankAIController::GetAITank() const
{
	return(Cast<ATank>(GetPawn()));
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return PlayerTank;
}
