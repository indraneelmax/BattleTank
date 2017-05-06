// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PLayerController class beginPlay"));
	auto ControlledTank = GetPawn();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PLayerController not possessing Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PLayerController possessing: %s"), *ControlledTank->GetName());
	}

	//IN begin Play stage, constructor of Aiming Component (added in BP) should have been called
	//hence aiming comp should exist by now
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller could not find Aiming Component"));
	}
	else 
	{
		//Call this event passing the aiming comp which will trigger UI (crosshair) creation
		FoundAimingComponent(AimingComponent);
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PLayerController %s Ticking"), *GetControlledTank()->GetName());
	AimAtCrosshair();

}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller could not find Aiming Component"));
		return;
	}
	else {
		//if the crosshair intersects landscape through raytracing
		//MOve the barrel towards crosshair
		FVector HitLocation; // OUT Parameter
		if (GetCrossHairHitLocation(HitLocation))
		{
			AimingComponent->AimAt(HitLocation);
			//UE_LOG(LogTemp, Warning, TEXT("Crosshair Hit Location: %s"),*HitLocation.ToString() )
		}
	}
}

// This function will modify HitLocation as its a Reference!
bool ATankPlayerController::GetCrossHairHitLocation(FVector& HitLocation) 
{
	//Find the crosshair position in pixel coordinates 2D

	HitLocation = FVector(1.0f);
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//Location of Crosshair in 2D is 50% (CrosshairXLocation) in X and 33% in Y of ViewPortSize
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

	//"De project" the screen position of the crosshair to a world direction
	FVector LookDirection; // This is the look direction based on crosshair screen location
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
		// Line trace along the look direction and see what we hit (within a max)
		FHitResult HitResult;
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;

}
bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const 
{
	FVector CameraWorldLocation; // this will be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}


