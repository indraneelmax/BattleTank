// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category= "State")
	EFiringState FiringState = EFiringState::Locked;
public:	

	void AimAt(FVector HitLocation, float LaunchSpeed);
	UFUNCTION(BlueprintCallable, Category = Setups)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection);
};
