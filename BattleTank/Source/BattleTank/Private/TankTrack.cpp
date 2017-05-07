// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay()
{
	//OnComponentHit is an Event which is registering to call OnHit function
	//This OnComponentHit can be added through BP but we are doing throug C++
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);	
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Signature of this function found thru OnComponentHit definition -> FComponentHitSignature defintiion
	//UE_LOG(LogTemp, Warning, TEXT("I am HIt ! I am HIt!"));
	
	//Previously driveTrack was inside SetThrottle func
	//To make sure that when track is on ground we apply forces
	//we moved out force apply code into DriveTrack
	//And only set CurrentThrottle via TankMovementComponet
	ApplySideWaysForce();
	DriveTrack();
	//We need to reset otherwise last value will be retained and tank continues
	CurrentThrottle = 0;
}


void UTankTrack::ApplySideWaysForce()
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
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto acceleration = SlippageSpeed / DeltaTime * GetRightVector(); // direction of acceleration
	auto CorrectionForce = TankRoot->GetMass() * (-acceleration); //negated
	//Apply the negating force to Tank
	TankRoot->AddForce(CorrectionForce/2); //Apply half as we have two track!
	//UE_LOG(LogTemp, Warning, TEXT("Applying Sideways Force : %s"), *CorrectionForce.ToString());
	
}

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle += throttle;
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle, -1, 1);


}
void UTankTrack::DriveTrack()
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //get this tracks pivot
	//Get Root component of tank and apply force on it
	// Root component is USceneComponent but that does not allow force to be applied
	// Hence cast it to UPrimit (its super is UScene check class hierarchy)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}