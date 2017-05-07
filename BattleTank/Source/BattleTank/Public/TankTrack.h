// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UTankTrack();
	virtual void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float TankMaxDrivingForce = 400000;  // <- 40tonne with 1g acceleration in Newton
	
};
