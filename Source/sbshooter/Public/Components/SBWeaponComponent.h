// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBWeaponComponent.generated.h"

class ASBBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SBSHOOTER_API USBWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USBWeaponComponent();

	void Fire();	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<ASBBaseWeapon> WeaponClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")

		FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

public:	

private:
	UPROPERTY ()
		ASBBaseWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();

		
};
