// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank; //Forward Declaration
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
public:
	//ATank* GetControlledTank() const;
	float AcceptanceRadius = 3000;
	//ATank* GetPlayerTank() const;
};
