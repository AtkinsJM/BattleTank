// Copyright Joshua Atkins

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(PhysicsConstraint);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		
	//PhysicsConstraint->SetConstrainedComponents(Mass, FName("BoneName1"), Wheel, FName("BoneName2"));
	//PhysicsConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	//PhysicsConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	//PhysicsConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 100.0f);
	//PhysicsConstraint->SetLinearPositionDrive(false, false, true);
	//PhysicsConstraint->SetLinearDriveParams(50.0f, 10.0f, 0.0f);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

