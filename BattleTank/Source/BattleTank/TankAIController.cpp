// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
//FYI: TankAICont Depends on TankMovementComponent via Pathfinding !

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController class beginPlay"));
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!ControlledTank || !PlayerTank)
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
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		auto ControlledTank = GetControlledTank();
		//Move towards the player
		//Uses AI pathfinding --calls our overriden method
		//RequestDirectMove in TankMovementComponent!
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim & Fire at Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerPawn)) { return nullptr; }
	
	return Cast<ATank>(PlayerPawn);
}


