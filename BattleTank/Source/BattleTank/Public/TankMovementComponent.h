// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	//Even though in tank.h the obj/ptr of this class is blueprintReadOnly
	// we need to make IntendTankMoveForward blueprintcallable to get 
	// the method as well accesible in blueprint graph
	UFUNCTION(BlueprintCallable, Category= Input)
	void IntendTankMoveForward(float Throw);	
	
};
