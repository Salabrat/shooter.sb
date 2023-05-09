// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SBHealthPercentDecorator.generated.h"

UCLASS()
class SBSHOOTER_API USBHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	USBHealthPercentDecorator();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float HealthPercent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
