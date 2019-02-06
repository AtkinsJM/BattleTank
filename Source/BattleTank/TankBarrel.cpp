// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float ElevationDirection)
{
	float PitchChange = ElevationDirection * MaxDegsPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewPitch = RelativeRotation.Pitch + PitchChange;
	float ClampedPitch = FMath::Clamp(NewPitch, MinPitch, MaxPitch);
	SetRelativeRotation(FRotator(ClampedPitch, 0, 0));
}