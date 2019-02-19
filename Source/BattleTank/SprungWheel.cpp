// Copyright Joshua Atkins

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;

	//Get basic static mesh (change later)
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* StaticMesh = MeshAsset.Object;

	//Create physics constraint component and set as root
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(PhysicsConstraint);
	/*
	//Create and initialise mass static mesh component
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetupAttachment(RootComponent);
	Mass->SetMobility(EComponentMobility::Movable);
	Mass->SetRelativeLocation(FVector(0.0f, 0.0f, VerticalOffset));
	Mass->SetSimulatePhysics(true);
	if (StaticMesh) { Mass->SetStaticMesh(StaticMesh); }
	*/
	//Create and initialise wheel static mesh component
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(RootComponent);
	Wheel->SetMobility(EComponentMobility::Movable);
	Wheel->SetRelativeLocation(FVector(0.0f, 0.0f, -VerticalOffset));
	Wheel->SetSimulatePhysics(true);
	if (StaticMesh) { Wheel->SetStaticMesh(StaticMesh); }

	//Initialise physics constraint
	PhysicsConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	PhysicsConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	PhysicsConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, VerticalLinearLimit);
	PhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraint->SetLinearPositionDrive(false, false, true);
	PhysicsConstraint->SetLinearDriveParams(LinearDrivePositionStrength, LinearDriveVelocityStrength, 0.0f);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* VehicleBody = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!VehicleBody || !Wheel) { return; }
	//Set constrained components (at run time to aovid warning about mesh mobility)
	Wheel->SetMassOverrideInKg(NAME_None, VehicleBody->GetMass() / 10.0f, true);
	PhysicsConstraint->SetConstrainedComponents(VehicleBody, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

