// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SBCharacterMovementComponent.generated.h"


UCLASS()
class SBSHOOTER_API USBCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
		float RunModifier = 2.0f;
	virtual float GetMaxSpeed() const override;
};
