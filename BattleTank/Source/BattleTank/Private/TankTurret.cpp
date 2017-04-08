// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("Move to Pitch: %f "), pitch);
	// RelativeSpeed is clamped btw -1 to +1 
	// As the turret moves with maxspeed always
	auto speed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto rotationChange = speed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto newRawrotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0, newRawrotation, 0));


}




