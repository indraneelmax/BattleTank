// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate); // Implementing OnDeath - Dynamic Delegate

class UTankBarrel; // Forward Declaration
class UTankTurret;
class AProjectile;
//class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:

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

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

public:
	//makes this read only function that does not change anything
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealthPercent() const;
	//Called by the Engine itself when a ApplyDamage is called by projectile for us
	virtual float TakeDamage(float Damage,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		class AActor* DamageCauser);
	FTankDelegate OnDeath; //Declaring the death event
};
