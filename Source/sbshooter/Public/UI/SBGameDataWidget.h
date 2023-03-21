// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBGameDataWidget.generated.h"

class ASBGameModeBase;
class ASBPlayerState;

UCLASS()
class SBSHOOTER_API USBGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetCurrentRoundNum() const;


	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetRoundSecodsRemaining() const;
private:
	ASBGameModeBase* GetSBGameMode() const;
	ASBPlayerState* GetSBPlayerState() const;
};
