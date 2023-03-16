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

	SpawnWeapon();
}

void USBWeaponComponent::SpawnWeapon()
{	
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(),AttachmentRules, WeaponAttachPointName);
	CurrentWeapon -> SetOwner(Character);
	

	/*const auto Weapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponClass);
	if (Weapon)
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Weapon->AttachToComponent(GetMesh(), AttachmentRules, "WeaponSocket");
	}
	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}*/
}


void USBWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}