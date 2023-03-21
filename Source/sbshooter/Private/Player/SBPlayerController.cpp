// Salabrat Game, All rights Reserved. SB4


#include "Player/SBPlayerController.h"
#include "Components/SBRespawnComponent.h"

ASBPlayerController::ASBPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USBRespawnComponent>("RespawnComponent");
}

void ASBPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}