// Salabrat Game, All rights Reserved. SB4


#include "AI/Services/SBChangeWeaponService.h"
#include "Components/SBWeaponComponent.h"
#include "AIController.h"
#include "SBUtils.h"

USBChangeWeaponService::USBChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USBChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
