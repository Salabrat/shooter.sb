// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBCoreTypes.h"
#include "SBPlayerHUDWidget.generated.h"

class USBWeaponComponent;

UCLASS()
class SBSHOOTER_API USBPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

private:
	USBWeaponComponent* GetWeaponComponent() const;
	
};
