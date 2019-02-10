// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float ElevationDirection);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegsPerSecond = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxPitch = 30.0f;	//Degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinPitch = 0.0f;	//Degrees
};
