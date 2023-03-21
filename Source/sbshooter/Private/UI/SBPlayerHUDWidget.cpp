// Salabrat Game, All rights Reserved. SB4


#include "UI/SBPlayerHUDWidget.h"
#include "Components/SBHealthComponent.h"
#include "Components/SBWeaponComponent.h"
#include "SBUtils.h"

bool USBPlayerHUDWidget::Initialize()
{
	if (GetOwningPlayer())
	{	
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USBPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
		//test
		OnNewPawn(GetOwningPlayerPawn());
		OnNewPawn(GetOwningPlayerPawn());
	}
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USBPlayerHUDWidget::OnHealthChanged);

	}
	return Super::Initialize();
}

void USBPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(NewPawn);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USBPlayerHUDWidget::OnHealthChanged);
	}	
}

void USBPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0.0f)
	{
	OnTakeDamage();
	}
}


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