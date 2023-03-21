// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SBSHOOTER_API USBRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USBRespawnComponent();

	void Respawn(int32 RespawnTime);
	int32 GetRespawnCountDown() const { return RespawnCountDown; }
	bool IsRespawnInProgress() const;
private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();

public:	

		
};
