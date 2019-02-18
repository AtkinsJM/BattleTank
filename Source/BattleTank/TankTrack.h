// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTack is used to maximum maximum driving force and apply force to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UTankTrack();

protected:
	virtual void BeginPlay() override;

	void ApplySidewaysCorrectionForce();
	
public:
	void SetThrottle(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void DriveTrack();

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MaxDrivingForce = 60000000.0f;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	float CurrentThrottle = 0;
};
