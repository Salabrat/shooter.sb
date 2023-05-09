// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class SBSHOOTER_API USBGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
		UPROPERTY(meta = (BindWidget))
		UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;

	private:

	UFUNCTION()
		void OnGoToMenu();
};