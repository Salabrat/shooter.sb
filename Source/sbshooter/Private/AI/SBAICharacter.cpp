// Salabrat Game, All rights Reserved. SB4


#include "AI/SBAICharacter.h"
#include "AI/SBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SBAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/SBHealthBarWidget.h"
#include "Components/SBHealthComponent.h"

ASBAICharacter::ASBAICharacter(const FObjectInitializer& ObjInit)
: Super(ObjInit.SetDefaultSubobjectClass<USBAIWeaponComponent>("WeaponComponent"))

{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASBAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASBAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void ASBAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto SBController = Cast<AAIController>(Controller);
	if (SBController && SBController->BrainComponent)
	{
		SBController->BrainComponent->Cleanup();
	}
}
void ASBAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto HealthBarWidget = Cast<USBHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());

}
