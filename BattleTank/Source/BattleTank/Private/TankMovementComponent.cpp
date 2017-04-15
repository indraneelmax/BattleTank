// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendTankMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	//to move back the setting in input key binding have scale -1 
	//UE_LOG(LogTemp, Warning, TEXT("Intend Move forward throw:%f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTankTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//to turn left the setting in input key binding have scale -1 
	//UE_LOG(LogTemp, Warning, TEXT("Intend Move right throw:%f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// not calling super for this overriden method as we wish to change functionality
	auto TankName = GetOwner()->GetName();
	//Where AI Tank wants to move
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	//Where AI tank is currently looking
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// We are taking dot prod of AIFI and TF, dot prod tells me how much paraller 
	// are the two vect (if parralel then cos(0)= 1) so that prod value is what we
	// sent as throttle to move tank forward/backward
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendTankMoveForward(ForwardThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s AI tank move direction : %s "), *TankName, *MoveVelocityString);

	//For the turning of the AI tank we would do cross product of the same two unit vec,
	// The z component of resultant vec will go to the throttle to rightturn;
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	UE_LOG(LogTemp, Warning, TEXT("%s AI tank turn direction : %s "), *TankName,*RightThrow.ToString());
	IntendTankTurnRight(RightThrow.Z);
}



