// Salabrat Game, All rights Reserved. SB4


#include "Weapon/SBProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ASBProjectile::ASBProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

void ASBProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASBProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
}

void ASBProjectile::OnProjectileHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	//make damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), // 
		DamageAmount, //
		GetActorLocation(), //
		DamageRadius, //
		UDamageType::StaticClass(),
		{ GetOwner() }, //
		this, //
		GetController(), //
		DoFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
	//WeaponVFXComponent->PlayImpactFX(Hit);
	Destroy();
}

AController* ASBProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}