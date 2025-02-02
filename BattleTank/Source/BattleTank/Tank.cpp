// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
//#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//UE_LOG(LogTemp, Warning, TEXT("Donkey %s TAnk C++ Construct"), *GetName());
	//All tank aiming stuff dealt in a separate component
	//Added C++ way instead of blueprint way
	//Since Tank_BP inherits from Tank class, Tank_BP gets the component (inherits)
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
	
	//Below is code to attach a particle fx to tank as it would crash doing in BP
	//FireOnDeath = CreateDefaultSubobject<UParticleSystemComponent>(FName("Fire On Death"));
	//FireOnDeath->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//FireOnDeath->bAutoActivate = false; //Needs to activate on Death 
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PFIRE(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	//FireOnDeath->SetTemplate(PFIRE.Object);
}

// Called when the game starts or when spawned

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth; //Initialise health if set in Blueprint as well!
	//UE_LOG(LogTemp, Warning, TEXT("Donkey %s TAnk C++ Begin Play"), *GetName());
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

float ATank::TakeDamage(float Damage,
	struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator,
	class AActor* DamageCauser)
{
	//
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Damage: %d  ->  DamageToApply : %d "), DamagePoints, DamageToApply);

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank DIED"));
		//FireOnDeath->Activate();
		auto FireOnDeath = FindComponentByClass<UParticleSystemComponent>();
		FireOnDeath->Activate();
		OnDeath.Broadcast(); //Broadcast - let subscribers do what they want
		

	}
	return DamageToApply;
}

float ATank::GetCurrentHealthPercent() const
{
	return  float(CurrentHealth)/ float(StartingHealth);
}