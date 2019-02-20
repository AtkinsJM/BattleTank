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
	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(AxleConstraint);
	
	//Create and initialise mass static mesh component
	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	Axle->SetupAttachment(RootComponent);
	Axle->SetMobility(EComponentMobility::Movable);
	Axle->SetRelativeLocation(FVector(0.0f, 0.0f, -AxleOffset));
	Axle->SetSimulatePhysics(true);
	if (StaticMesh) { Axle->SetStaticMesh(StaticMesh); }
	
	//Create and initialise wheel static mesh component
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(RootComponent);
	Wheel->SetMobility(EComponentMobility::Movable);
	Wheel->SetRelativeLocation(FVector(0.0f, WheelOffset, -AxleOffset));
	Wheel->SetSimulatePhysics(true);
	if (StaticMesh) { Wheel->SetStaticMesh(StaticMesh); }
	
	//Initialise physics constraint
	AxleConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	AxleConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	AxleConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, VerticalLinearLimit);
	AxleConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetLinearPositionDrive(false, false, true);
	AxleConstraint->SetLinearDriveParams(LinearDrivePositionStrength, LinearDriveVelocityStrength, 0.0f);

	
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
	if (!VehicleBody || !Axle || !Wheel) { return; }
	//Set constrained components (at run time to aovid warning about mesh mobility)
	Wheel->SetMassOverrideInKg(NAME_None, VehicleBody->GetMass() / 10.0f, true);
	AxleConstraint->SetConstrainedComponents(VehicleBody, NAME_None, Axle, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

