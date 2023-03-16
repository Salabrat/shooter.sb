// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SBSHOOTER_API ASBProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
};
