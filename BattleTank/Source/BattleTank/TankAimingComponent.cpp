// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
//Need to include below as we call methods on Barrel object
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();

}
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("AIming component TICKING"));
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Aiming ...."));
		FiringState = EFiringState::Aiming;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT(" LOCKED HA HA ...."));
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	//(LogTemp, Warning, TEXT("BArrel ---  %s"), *BarrelForward.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Aiming ...."), *AimDirection.ToString());
	return !BarrelForward.Equals(AimDirection, 0.01);

}
void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Launch Speed: %f"), LaunchSpeed);
	
	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s hitting at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool result = UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0
		,ESuggestProjVelocityTraceOption::DoNotTrace //Buggy Line, just comment to see bug
	);

	if (result)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: %s Projectile Direction calculated as %s"),Time, *OurTankName, *AimDirection.ToString());
		//Move the Barrel
		//Barrel->MoveTo(AimDirection.Rotation().Pitch);
		//Unused 
		MoveBarrelTowards();
	}
	else
	{ // NO result found
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : NO result found"), Time);

	}
}


void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel && Turret)) { return; }
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("Move Barrel to %s"), *DeltaRotator.ToString());
	// Move the barrel according to elevation speed just the right amount
	// this frame
	Barrel->MoveTo(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
}


void UTankAimingComponent::Fire()
{
	//FPlatformTime::Seconds()  returns a "double" type
	// can use GetWorld()->GetTimeSeconds() as well below
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel does not exist: %s"), *GetName());
		return;
	}
	//enabling below line crashes, although it does the same thing as above if statment
	//Fails immediately since Aicontroller in tick calls FIRE every frame!
	//if (!ensure(Barrel)) { return; }
	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		if (!Projectile)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Projectile to fire!!"));
			return;
		}
		//TODO Fix firing
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		
	}
}