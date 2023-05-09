// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBHealthPickup.generated.h"

UCLASS()
class SBSHOOTER_API ASBHealthPickup : public ASBBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		float HealthAmount = 100.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
