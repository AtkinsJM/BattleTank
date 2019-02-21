// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;
/**
 * TankTack is used to maximum maximum driving force and apply force to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UTankTrack();
		
public:
	void SetThrottle(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MaxDrivingForce = 60000000.0f;

private:
	TArray<ASprungWheel*> GetWheels() const;
};
