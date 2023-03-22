// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBPauseWidget.generated.h"

class UButton;

UCLASS()
class SBSHOOTER_API USBPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* ClearPauseButton;

private:
	UFUNCTION()
		void OnClearPause();
};
