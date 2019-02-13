// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AITank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ensure(PlayerTank && TankAimingComponent))
	{
		//Move towards player until in range
		MoveToActor
		(
			PlayerTank,
			AcceptanceRadius
		);
		//Aim at player
		//TODO change to GetActorLocation? Check difference
		TankAimingComponent->AimAt(PlayerTank->GetTargetLocation());
		if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
		{
			//Fire
			TankAimingComponent->Fire();
		}
		
	}
}
