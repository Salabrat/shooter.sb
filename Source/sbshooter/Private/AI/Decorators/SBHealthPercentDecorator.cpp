// Salabrat Game, All rights Reserved. SB4


#include "AI/Decorators/SBHealthPercentDecorator.h"
#include "AIController.h"
#include "SBUtils.h"
#include "Components/SBHealthComponent.h"

USBHealthPercentDecorator::USBHealthPercentDecorator()
{
	NodeName = "HealthPercent";
}


bool USBHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
