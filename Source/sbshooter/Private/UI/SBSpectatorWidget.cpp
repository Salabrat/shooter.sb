// Salabrat Game, All rights Reserved. SB4


#include "UI/SBSpectatorWidget.h"
#include "SBUtils.h"
#include "Components/SBRespawnComponent.h"

bool USBSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = SBUtils::GetSBPlayerComponent<USBRespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}

