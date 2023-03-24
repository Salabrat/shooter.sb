// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Player/SBBaseCharacter.h"
#include "SBAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SBSHOOTER_API ASBAICharacter : public ASBBaseCharacter
{
	GENERATED_BODY()

public:
	ASBAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* UBehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float HealthVisibilityDistance = 1000.0f;

	virtual void BeginPlay() override;
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};
