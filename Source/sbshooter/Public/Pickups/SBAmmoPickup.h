// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBAmmoPickup.generated.h"

class ASBBaseWeapon;

UCLASS()
class SBSHOOTER_API ASBAmmoPickup : public ASBBasePickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
		int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		TSubclassOf<ASBBaseWeapon> WeaponType;


private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

	
};
