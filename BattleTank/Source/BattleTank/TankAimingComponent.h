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
class AProjectile;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category= "State")
	EFiringState FiringState = EFiringState::Locked;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	double LastFireTime = 0; // by default with f e.g 1f it returns a double type
	FVector AimDirection;
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;  //speed of projectile 40 m/s
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 3; //sec 
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf <AProjectile> ProjectileBlueprint;

public:	

	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setups)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
	
	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);
};
