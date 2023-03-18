// Salabrat Game, All rights Reserved. SB4


#include "Pickups/SBAmmoPickup.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASBAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	return true;
}
