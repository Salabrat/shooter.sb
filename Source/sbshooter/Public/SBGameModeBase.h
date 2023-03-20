// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SBCoreTypes.h"
#include "SBGameModeBase.generated.h"

class AAIController;

UCLASS()
class SBSHOOTER_API ASBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASBGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FGameData GameData;
private:
	void SpawnBots();

};
