// Copyright Joshua Atkins

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
//#include "UObject/ConstructorHelpers.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//Create physics constraint component and set as root
	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	SetRootComponent(AxleConstraint);
	
	//Create and initialise mass static mesh component
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(RootComponent);
	Axle->SetMobility(EComponentMobility::Movable);
	Axle->SetRelativeLocation(FVector(0.0f, 0.0f, -AxleOffset));
	Axle->SetSimulatePhysics(true);
	Axle->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Axle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Axle->bHiddenInGame = false;
	
	//Create physics constraint component and set as root
	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Wheel Constraint"));
	WheelConstraint->SetupAttachment(Axle);

	//Create and initialise wheel static mesh component
	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	Wheel->SetMobility(EComponentMobility::Movable);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Wheel->bHiddenInGame = false;
	
	//Initialise physics constraint
	AxleConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	AxleConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	AxleConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, VerticalLinearLimit);
	AxleConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetLinearPositionDrive(false, false, true);
	AxleConstraint->SetLinearDriveParams(LinearDrivePositionStrength, LinearDriveVelocityStrength, 0.0f);
	
	WheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	WheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0.0f);
	WheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	
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
	if (!VehicleBody || !Axle || !Wheel || !AxleConstraint || !WheelConstraint) { return; }
	//Set constrained components (at run time to aovid warning about mesh mobility)
	UE_LOG(LogTemp, Warning, TEXT("Setting constrained components."));
	Axle->SetMassOverrideInKg(NAME_None, VehicleBody->GetMass() / 10.0f, true);
	Wheel->SetMassOverrideInKg(NAME_None, VehicleBody->GetMass() / 10.0f, true);
	AxleConstraint->SetConstrainedComponents(VehicleBody, NAME_None, Axle, NAME_None);
	WheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

