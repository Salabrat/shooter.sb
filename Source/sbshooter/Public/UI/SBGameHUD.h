// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SBCoreTypes.h"
#include "SBGameHUD.generated.h"

UCLASS()
class SBSHOOTER_API ASBGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
		TMap<ESBMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;

	void DrawCrossHair();
	void OnMatchStateChanged(ESBMatchState State);
};
