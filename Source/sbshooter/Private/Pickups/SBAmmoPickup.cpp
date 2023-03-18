// Salabrat Game, All rights Reserved. SB4


#include "Pickups/SBAmmoPickup.h"
#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"
#include "SBUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASBAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
