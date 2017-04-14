// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving Tank Tracks forward 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	//Even though in tank.h the obj/ptr of this class is blueprintReadOnly
	// we need to make IntendTankMoveForward blueprintcallable to get 
	// the method as well accesible in blueprint graph
	UFUNCTION(BlueprintCallable, Category= Input)
	void IntendTankMoveForward(float Throw);	
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTankTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
};
