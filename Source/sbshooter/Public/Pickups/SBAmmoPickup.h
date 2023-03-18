// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SBSHOOTER_API ASBAmmoPickup : public ASBBasePickup
{
	GENERATED_BODY()

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
