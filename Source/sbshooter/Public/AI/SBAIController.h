// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SBAIController.generated.h"

UCLASS()
class SBSHOOTER_API ASBAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
