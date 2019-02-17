// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//TODO consider moving to SetPawn (to ensure pawn is set before attempting to retrieve
	AITank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!AITank) { return; }
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	AITank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
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

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *GetName());
}
