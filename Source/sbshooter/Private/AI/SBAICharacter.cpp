// Salabrat Game, All rights Reserved. SB4


#include "AI/SBAICharacter.h"
#include "AI/SBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SBAIWeaponComponent.h"
#include "BrainComponent.h"


ASBAICharacter::ASBAICharacter(const FObjectInitializer& ObjInit)
: Super(ObjInit.SetDefaultSubobjectClass<USBAIWeaponComponent>("WeaponComponent"))

{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASBAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
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