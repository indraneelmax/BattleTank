// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward Declaration
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
//class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	//Below is the Fly-by-wire component
	//helps in keeping AI also use same controls instead of 
	//directly translating tank for a fair game!
	//BlueprintReadOnly makes this component draggable into graph
	//basically youa can acess this variable in blueprint now
	//UPROPERTY(BlueprintReadOnly) 
	//UTankMovementComponent* TankMovementComponent = nullptr;

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
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3; //sec 
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf <AProjectile> ProjectileBlueprint;
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;  //speed of projectile 40 m/s
	double LastFireTime = 0; // by default with f e.g 1f it returns a double type
};
