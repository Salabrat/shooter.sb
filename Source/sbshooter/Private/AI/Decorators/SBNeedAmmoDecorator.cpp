// Salabrat Game, All rights Reserved. SB4


#include "AI/Decorators/SBNeedAmmoDecorator.h"
#include "AIController.h"
#include "SBUtils.h"
#include "Components/SBWeaponComponent.h"

USBNeedAmmoDecorator::USBNeedAmmoDecorator()
{
	NodeName = "NeedAmmoSB";
}

bool USBNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = SBUtils::GetSBPlayerComponent<USBWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
