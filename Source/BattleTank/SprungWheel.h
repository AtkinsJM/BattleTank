// Copyright Joshua Atkins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Physics Constraint")
		UPhysicsConstraintComponent* AxleConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Physics Constraint")
		UPhysicsConstraintComponent* WheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Physics Constraint")
		USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Physics Constraint")
		USphereComponent* Axle = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:
	void SetupConstraint();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float VerticalLinearLimit = 25.0f;	
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float LinearDrivePositionStrength = 75.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float LinearDriveVelocityStrength = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float AxleOffset = 85.0f;

	float CurrentForce = 0.0f;
};
