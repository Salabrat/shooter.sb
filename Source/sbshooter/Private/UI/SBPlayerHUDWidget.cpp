// Salabrat Game, All rights Reserved. SB4


#include "UI/SBPlayerHUDWidget.h"
#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"

float USBPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USBPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USBPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);		
}

bool USBPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	return HealthComponent && !HealthComponent->IsDead();
}

bool USBPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

USBWeaponComponent* USBPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USBWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USBWeaponComponent>(Component);
	return WeaponComponent;

}
 
USBHealthComponent* USBPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USBHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USBHealthComponent>(Component);
	return HealthComponent;

}