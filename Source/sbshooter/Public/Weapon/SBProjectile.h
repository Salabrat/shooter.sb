// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBProjectile.generated.h"

class USphereComponent;

UCLASS()
class SBSHOOTER_API ASBProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		USphereComponent* CollisionComponent;


};
