// Salabrat Game, All rights Reserved. SB4


#include "SBGameModeBase.h"
#include "Player/SBBaseCharacter.h"
#include "Player/SBPlayerController.h"
#include "UI/SBGameHUD.h"

ASBGameModeBase::ASBGameModeBase()
{
	DefaultPawnClass = ASBBaseCharacter::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
	HUDClass = ASBGameHUD::StaticClass();
}