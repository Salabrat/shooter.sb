// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBFindEnemyService.generated.h"

UCLASS()
class SBSHOOTER_API USBFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USBFindEnemyService();

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
