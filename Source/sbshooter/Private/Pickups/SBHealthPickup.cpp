// Salabrat Game, All rights Reserved. SB4


#include "Pickups/SBHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASBHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
	return true;
}