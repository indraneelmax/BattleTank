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
	float CurrentThrottle = 0;
	virtual void BeginPlay() override;
	virtual void UTankTrack::ApplySideWaysForce();
	void DriveTrack();
	//Signature of OnHit function found thru OnComponentHit definition -> FComponentHitSignature defintiion
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float TankMaxDrivingForce = 400000;  // <- 40tonne with 1g acceleration in Newton
	
};
