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
	UE_LOG(LogTemp, Warning, TEXT("Intend Move right throw:%f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}




