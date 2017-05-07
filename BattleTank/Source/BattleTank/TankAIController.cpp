// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
//FYI: TankAICont Depends on TankMovementComponent via Pathfinding !

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController class beginPlay"));
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(ControlledTank && PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s found Player: %s"), *ControlledTank->GetName(), *PlayerTank->GetName());	
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaSeconds)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
	{
		auto ControlledTank = GetPawn();
		//Move towards the player
		//Uses AI pathfinding --calls our overriden method
		//RequestDirectMove in TankMovementComponent!
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim & Fire at Player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		//Fire only if Target locked
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	}
}


