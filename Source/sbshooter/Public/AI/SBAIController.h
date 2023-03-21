// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SBAIController.generated.h"

class USBAIPerceptionComponent;
class USBRespawnComponent;

UCLASS()
class SBSHOOTER_API ASBAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASBAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USBAIPerceptionComponent* SBAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USBRespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};
