// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Player/SBBaseCharacter.h"
#include "SBAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SBSHOOTER_API ASBAICharacter : public ASBBaseCharacter
{
	GENERATED_BODY()

public:
	ASBAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* UBehaviorTreeAsset;
};
