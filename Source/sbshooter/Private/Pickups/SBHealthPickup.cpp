// Salabrat Game, All rights Reserved. SB4


#include "Pickups/SBHealthPickup.h"
#include "Components/SBHealthComponent.h"
#include "SBUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASBHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;
	return HealthComponent->TryToAddHealth(HealthAmount);
}