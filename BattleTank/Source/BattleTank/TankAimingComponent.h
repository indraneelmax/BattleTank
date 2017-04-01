// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void AimAt(FVector HitLocation, float LaunchSpeed);

	UStaticMeshComponent* Barrel = nullptr;

	UTankAimingComponent();

	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
	void MoveBarrelTowards(FVector AimDirection);
};
