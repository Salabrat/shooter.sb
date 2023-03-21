// Salabrat Game, All rights Reserved. SB4

#include "Components/SBRespawnComponent.h"
#include "SBGameModeBase.h"

//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
USBRespawnComponent::USBRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USBRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USBRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void USBRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
