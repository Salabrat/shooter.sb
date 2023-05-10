// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "UI/SBBaseWidget.h"
#include "SBCoreTypes.h"
#include "SBMenuWidget.generated.h" 

class UButton;
class UHorizontalBox;
class USBGameInstance;
class USBLevelItemWidget;

UCLASS()
class SBSHOOTER_API USBMenuWidget : public USBBaseWidget
{
	GENERATED_BODY()

protected:
		UPROPERTY(meta = (BindWidget))
		 UButton* StartGameButton;

		UPROPERTY(meta = (BindWidget))
			UButton* QuitGameButton;

		UPROPERTY(meta = (BindWidget))
			UHorizontalBox* LevelItemsBox;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
			TSubclassOf<UUserWidget> LevelItemWidgetClass;

		UPROPERTY(Transient, meta = (BindWidgetAnim))
			UWidgetAnimation* HideAnimation;

		virtual void NativeOnInitialized() override;
		virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	UPROPERTY()
		TArray<USBLevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
		void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	USBGameInstance* GetSBGameInstance() const;
};
