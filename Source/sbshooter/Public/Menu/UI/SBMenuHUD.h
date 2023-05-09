// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SBMenuHUD.generated.h"

UCLASS()
class SBSHOOTER_API ASBMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void BeginPlay() override;
};