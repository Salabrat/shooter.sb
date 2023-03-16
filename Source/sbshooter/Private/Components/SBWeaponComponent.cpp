// Salabrat Game, All rights Reserved. SB4


#include "Components/SBWeaponComponent.h"
#include "Weapon/SBBaseWeapon.h"
#include "GameFramework/Character.h"

USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USBWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}


void USBWeaponComponent::SpawnWeapons()
{	
		ACharacter* Character = Cast<ACharacter>(GetOwner());
		if (!Character || !GetWorld()) return;

		for (auto WeaponClass : WeaponClasses)
		{
			auto Weapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponClass);
			if (!Weapon) continue;

			//Weapon->OnClipEmpty.AddUObject(this, &USBWeaponComponent::OnEmptyClip);
			Weapon->SetOwner(Character);
			Weapons.Add(Weapon);

			AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
		}
	
}

void USBWeaponComponent::AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USBWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	/*if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
	UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid Weapon Index"));
		return;
	}*/

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	/*CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {
		return Data.WeaponClass == CurrentWeapon->GetClass();
		});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;*/
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	//PlayAnimMontage(EquipAnimMontage);
}

void USBWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}


void USBWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USBWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
