// Salabrat Game, All rights Reserved. SB4


#include "Player/SBPlayerController.h"
#include "Components/SBRespawnComponent.h"

ASBPlayerController::ASBPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USBRespawnComponent>("RespawnComponent");
}


