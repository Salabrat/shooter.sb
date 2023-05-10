// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBBaseWidget.generated.h"

UCLASS()
class SBSHOOTER_API USBBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void Show();

protected:
    UPROPERTY(Transient, meta = (BindWidgetAnim))
        UWidgetAnimation* ShowAnimation;

};
   // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
      //  USoundCue* OpenSound;
