// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //NO need to tick as we dont have anything for that!
	//Add c++ way a collision mesh and set emit collision events true along with visibility
	//Set this as the root of the Projectile_BP
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	//Add "ProjectileMovementComponent" C++ way
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false; //Do not Launch until Fire

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false; //Needs to activate on IMPACT 

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	/*
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PFIRE(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PEXPLOSION(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion''"));
	ImpactBlast->SetTemplate(PFIRE.Object);
	LaunchBlast->SetTemplate(PEXPLOSION.Object);
	*/
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::LaunchProjectile(float Speed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Launch Projectile %f"), Speed);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast); //we want to destroy/delete our collisionmesh but before have to unset as root
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius, //Its a radial damage system so we use the centre of explosion itself
		UDamageType::StaticClass(),
		TArray<AActor*>()); //No list of actors passed i.e. affect all actors in Radius

	FTimerHandle Timer; //OUT parameter in below
	//Sets a Timer for DeostroyDelay seconds and call OnTimerExpire !
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy(); //Destroy yourself!
}
