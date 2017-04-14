// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *Name, throttle);
	auto ForceApplied = GetForwardVector() * throttle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //get this tracks pivot
	//Get Root component of tank and apply force on it
	// Root component is USceneComponent but that does not allow force to be applied
	// Hence cast it to UPrimit (its super is UScene check class hierarchy)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

