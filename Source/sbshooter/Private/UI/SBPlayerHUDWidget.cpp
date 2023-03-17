// Salabrat Game, All rights Reserved. SB4


#include "UI/SBPlayerHUDWidget.h"
#include "Components/SBHealthComponent.h"

float USBPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USBHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USBHealthComponent>(Component);
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}
