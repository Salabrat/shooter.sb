// Salabrat Game, All rights Reserved. SB4


#include "AI/SBAICharacter.h"
#include "AI/SBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASBAICharacter::ASBAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
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