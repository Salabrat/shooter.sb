// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SBGameInstance.generated.h"

UCLASS()
class SBSHOOTER_API USBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FName GetStartupLevelName() const { return StartupLevelName; }
	FName GetMenuLevelName() const { return MenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FName MenuLevelName = NAME_None;


};
