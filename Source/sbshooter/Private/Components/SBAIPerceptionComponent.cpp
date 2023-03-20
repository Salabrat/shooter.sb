// Salabrat Game, All rights Reserved. SB4


#include "Components/SBAIPerceptionComponent.h"
#include "AIController.h"
#include "SBUtils.h"
#include "Components/SBHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USBAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;
	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = SBUtils::GetSBPlayerComponent<USBHealthComponent>(PercieveActor);

		/*const auto	 PercievePawn = Cast<APawn>(PercieveActor);
		const auto AreEnemies = PercievePawn && SBUtils::AreEnemies(Controller, PercievePawn->Controller);*/

		if (HealthComponent && !HealthComponent->IsDead()) //&& AreEnemies) // TODO: check if enemies or not 
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}