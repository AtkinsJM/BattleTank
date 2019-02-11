 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declarations
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AActor* PlayerTank = nullptr;
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairPosX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairPosY = 0.333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;
	//Moves tank barrel to point towards crosshair
	void AimTowardsCrosshair();
	bool GetAimRayHitLocation(OUT FVector& HitLocation) const;
	bool GetLookVectorHitLocation(FVector WorldLocation, FVector LookDirection, OUT FVector& HitLocation) const;
};
