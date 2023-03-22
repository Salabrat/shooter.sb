// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBMenuWidget.generated.h"

class UButton;

UCLASS()
class SBSHOOTER_API USBMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
		UPROPERTY(meta = (BindWidget))
		 UButton* StartGameButton;

		virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();
};
