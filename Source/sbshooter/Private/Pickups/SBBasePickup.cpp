// Salabrat Game, All rights Reserved. SB4


#include "Pickups/SBBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASBBasePickup::ASBBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
		
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);	
}

void ASBBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
}

// Called every frame
void ASBBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) //override
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

bool ASBBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASBBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBBasePickup::Respawn, RespawnTime);
}

void ASBBasePickup::Respawn()
{
	//GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}