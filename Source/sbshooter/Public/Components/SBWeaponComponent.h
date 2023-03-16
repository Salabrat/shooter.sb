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

	void StartFire();	
	void StopFire();	
	void NextWeapon();	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<TSubclassOf<ASBBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")

		FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* EquipAnimMontage;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY ()
		ASBBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASBBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;

	void SpawnWeapons();	
	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
};
