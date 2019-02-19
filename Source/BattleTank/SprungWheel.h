// Copyright Joshua Atkins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

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

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Physics Constraint")
		UPhysicsConstraintComponent* PhysicsConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Physics Constraint")
		UStaticMeshComponent* Wheel = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float VerticalLinearLimit = 100.0f;	
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float LinearDrivePositionStrength = 50.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float LinearDriveVelocityStrength = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Physics Constraint")
		float VerticalOffset = 100.0f;
};
