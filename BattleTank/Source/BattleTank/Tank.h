// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward Declaration
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
private:
	// Sets default values for this pawn's properties
	ATank();

	UTankBarrel* Barrel = nullptr; //local barrel 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf <AProjectile> ProjectileBlueprint;
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
	UFUNCTION(BlueprintCallable, Category= Setups)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setups)
	void SetTurretReference(UTankTurret* TurretToSet);
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000;  //speed of projectile 1000 m/s| Find a sensible value
};
