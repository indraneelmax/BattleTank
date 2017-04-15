// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void AimAtCrosshair();
	bool GetCrossHairHitLocation(FVector&);
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000; //10km in cm

	bool GetLookDirection(FVector2D&, FVector&) const;
	bool GetLookVectorHitLocation(FVector&, FVector&) const;
};
