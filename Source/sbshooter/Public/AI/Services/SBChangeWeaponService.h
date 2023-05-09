// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBChangeWeaponService.generated.h"

UCLASS()
class SBSHOOTER_API USBChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	USBChangeWeaponService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float Probability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
