 // Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBSpectatorWidget.generated.h"

UCLASS()
class SBSHOOTER_API USBSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetRespawnTime(int32& CountDownTime) const;
	
};
