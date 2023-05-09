// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Components/SBWeaponComponent.h"
#include "SBAIWeaponComponent.generated.h"

UCLASS()
class SBSHOOTER_API USBAIWeaponComponent : public USBWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
