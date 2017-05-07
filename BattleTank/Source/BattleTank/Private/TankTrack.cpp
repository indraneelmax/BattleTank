// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Find the Slippage Speed i.e. (magnitude) component of velocity sideways i.e along right vector
	auto myVelocity = GetComponentVelocity();
	auto myRightVector = GetRightVector();
	auto SlippageSpeed = FVector::DotProduct(myVelocity,myRightVector); 
	//Now calculate the force using above speed to be applied in opposite direction to stop
	//sideways movement.
	//GetOwner()->GetRootComponent() gives us a Scene Component type.
	//but we need our tank root "mass" which is basically on a Static MEsh Component, hence we
	//need to type cast that to StaticMeshComponent
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto acceleration = SlippageSpeed / DeltaTime * GetRightVector(); // direction of acceleration
	auto CorrectionForce = TankRoot->GetMass() * (-acceleration); //negated
	//Apply the negating force to Tank
	TankRoot->AddForce(CorrectionForce/2); //Apply half as we have two track!
	//UE_LOG(LogTemp, Warning, TEXT("Applying Sideways Force : %s"), *CorrectionForce.ToString());
	
}

void UTankTrack::SetThrottle(float throttle)
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *Name, throttle);
	auto ForceApplied = GetForwardVector() * throttle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //get this tracks pivot
	//Get Root component of tank and apply force on it
	// Root component is USceneComponent but that does not allow force to be applied
	// Hence cast it to UPrimit (its super is UScene check class hierarchy)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

