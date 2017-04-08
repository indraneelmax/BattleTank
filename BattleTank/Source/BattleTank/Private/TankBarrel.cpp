// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::MoveTo(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("Move to Pitch: %f "), pitch);
	// RelativeSpeed is clamped btw -1 to +1 
	// As the barrel moves with maxspeed always
	auto speed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto elevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto newRawElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp<float>(newRawElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(elevation, 0, 0));


}

