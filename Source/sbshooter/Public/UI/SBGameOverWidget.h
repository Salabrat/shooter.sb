// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBCoreTypes.h"
#include "SBGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SBSHOOTER_API USBGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
        UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
        TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

  UPROPERTY(meta = (BindWidget))
        UButton* ResetLevelButton;


     virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESBMatchState State);
    void UpdatePlayersStat();

   UFUNCTION()
        void OnResetLevel();
};
