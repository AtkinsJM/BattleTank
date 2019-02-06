// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float ElevationDirection)
{
	float ElevationChange = ElevationDirection * MaxDegsPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp(NewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}