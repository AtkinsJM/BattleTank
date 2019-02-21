// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

#define OUT

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	DriveTrack(Throttle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float AppliedForce = CurrentThrottle * MaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = AppliedForce / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, OUT Children);
	TArray<ASprungWheel*> Wheels;
	for (USceneComponent* Child : Children)
	{
		USpawnPoint* SpawnPointObj = Cast<USpawnPoint>(Child);
		if(SpawnPointObj) 
		{
			if (SpawnPointObj->GetWheel())
			{
				Wheels.Add(SpawnPointObj->GetWheel());
			}
		}
	}
	int NumberOfWheels = Wheels.Num();
	UE_LOG(LogTemp, Warning, TEXT("%s has %d wheels."), *GetName(), NumberOfWheels);
	return Wheels;
}
