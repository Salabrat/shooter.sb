// Salabrat Game, All rights Reserved. SB4


#include "Components/SBWeaponComponent.h"
#include "Weapon/SBBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SBEquipFinishedAnimNotify.h"

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
	if (!EquipAnimMontage) return;

	const auto NotifyEvents = EquipAnimMontage->Notifies; //AnimUtils::FindNotifyByClass<USTU_EquipFinishedAnimNotify>(EquipAnimMontage);
	for (auto NotifyEvent: NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<USBEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, & USBWeaponComponent::OnEquipFinished);
			break;
		}
	}
}
void USBWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp) 
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;
		EquipAnimInProgress = false;

}

bool USBWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress;
}
bool USBWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}

void USBWeaponComponent::Reload()
{
	PlayAnimMontage(CurrentReloadAnimMontage);
}