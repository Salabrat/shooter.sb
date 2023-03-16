// Salabrat Game, All rights Reserved. SB4


#include "Weapon/SBProjectile.h"
#include "Components/SphereComponent.h"

ASBProjectile::ASBProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);
}

void ASBProjectile::BeginPlay()
{
	Super::BeginPlay();
}

