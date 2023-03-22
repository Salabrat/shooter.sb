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
	FString TestString = "Hello game!";
};
