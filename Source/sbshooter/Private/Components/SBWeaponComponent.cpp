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
	PlayAnimMontage(EquipAnimMontage);
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
void USBWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent) 
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	if (Character->GetMesh() == MeshComponent)
	{
		UE_LOG(LogWeaponComponent, Display, TEXT("FINISHED_STOP"));
	}
}