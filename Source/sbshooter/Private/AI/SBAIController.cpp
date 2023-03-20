// Salabrat Game, All rights Reserved. SB4


#include "AI/SBAIController.h"
#include "AI/SBAICharacter.h"


void ASBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SBCharacter = Cast<ASBAICharacter>(InPawn);
	if (SBCharacter)
	{
		RunBehaviorTree(SBCharacter->UBehaviorTreeAsset);
	}
}