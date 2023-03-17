// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBCoreTypes.h"
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
	void Reload ();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<FWeaponData> WeaponData;

	
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

	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void SpawnWeapons();	
	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void ChandeClip();
};
