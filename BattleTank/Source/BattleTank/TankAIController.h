// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnyWhere, Category = "Setup")
	float AcceptanceRadius = 8000; //AI tanks starts moving if we exit 80m radius 
public:
	//ATank* GetControlledTank() const;
	
	//ATank* GetPlayerTank() const;
};
