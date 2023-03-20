// Salabrat Game, All rights Reserved. SB4


#include "AI/Services/SBFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h" 
#include "SBUtils.h"
#include "Components/SBAIPerceptionComponent.h"

USBFindEnemyService::USBFindEnemyService()
{
	NodeName = "Find Enemy";
}

void USBFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UE_LOG(LogTemp, Display, TEXT("find enemy"))
		const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = SBUtils::GetSBPlayerComponent<USBAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}