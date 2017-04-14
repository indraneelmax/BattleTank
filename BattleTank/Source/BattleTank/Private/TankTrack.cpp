// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float speed)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *Name, speed);

}

