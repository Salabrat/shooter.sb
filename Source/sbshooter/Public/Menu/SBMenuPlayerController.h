// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SBMenuPlayerController.generated.h"

UCLASS()
class SBSHOOTER_API ASBMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
