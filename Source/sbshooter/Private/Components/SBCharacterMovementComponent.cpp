// Salabrat Game, All rights Reserved. SB4


#include "Components/SBCharacterMovementComponent.h"
#include "Player/SBBaseCharacter.h"

float USBCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASBBaseCharacter* Player = Cast<ASBBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}