// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/SBRespawnComponent.h"
#include "SBCoreTypes.h"
#include "SBPlayerController.generated.h"

class USBRespawnComponent;

UCLASS()
class SBSHOOTER_API ASBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
		ASBPlayerController();
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USBRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnMatchStateChanged(ESBMatchState State);
	void OnMuteSound();

};
 