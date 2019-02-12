// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector ForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForwardDirection, ForwardIntention);
	float TurnThrow = FVector::CrossProduct(TankForwardDirection, ForwardIntention).Z;
	IntendMove(TurnThrow, ForwardThrow);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMove(float XAxis, float YAxis)
{
	if (YAxis < 0) { XAxis *= -1; }
	LeftTrack->SetThrottle(XAxis+YAxis);
	RightTrack->SetThrottle(YAxis-XAxis);
}
