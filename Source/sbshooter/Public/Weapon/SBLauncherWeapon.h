// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBLauncherWeapon.generated.h"

class ASBProjectile;

UCLASS()
class SBSHOOTER_API ASBLauncherWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf <ASBProjectile> ProjectileClass;

	virtual void MakeShot();
};
