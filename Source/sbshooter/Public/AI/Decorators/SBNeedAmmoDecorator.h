// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SBNeedAmmoDecorator.generated.h"

class ASBBaseWeapon;
UCLASS()
class SBSHOOTER_API USBNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	USBNeedAmmoDecorator();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<ASBBaseWeapon> WeaponType;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
