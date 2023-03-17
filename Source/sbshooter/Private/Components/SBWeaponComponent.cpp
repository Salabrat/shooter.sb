// Salabrat Game, All rights Reserved. SB4


#include "Components/SBWeaponComponent.h"
#include "Weapon/SBBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SBEquipFinishedAnimNotify.h"
#include "Animations/SBReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	InitAnimations();
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

		for (auto OneWeaponData : WeaponData)
		{
			auto Weapon = GetWorld()->SpawnActor<ASBBaseWeapon>(OneWeaponData.WeaponClass);
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
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid Weapon Index"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	/*CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;*/
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void USBWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	CurrentWeapon->StartFire();
}


void USBWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USBWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USBWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USBWeaponComponent::InitAnimations() 
{
	auto EquipFinishedNotify = FindNotifyByClass<USBEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}
	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = FindNotifyByClass<USBReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify) continue;
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnReloadFinished);
	}

}

void USBWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp) 
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;
		EquipAnimInProgress = false;

}

void USBWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;

	ReloadAnimInProgress = false;
}

bool USBWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}
bool USBWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USBWeaponComponent::CanReload() const
{
	return CurrentWeapon//
		&& !EquipAnimInProgress//
		&& !ReloadAnimInProgress;
		//&& CurrentWeapon->CanReload();
}


void USBWeaponComponent::Reload()
{

	if (!CanReload()) return; 
	/*CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();*/
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}