// Salabrat Game, All rights Reserved. SB4


#include "Menu/SBMenuGameModeBase.h"
#include "Menu/SBMenuPlayerController.h"
#include "Menu/UI/SBMenuHUD.h"

ASBMenuGameModeBase::ASBMenuGameModeBase()
{
    PlayerControllerClass = ASBMenuPlayerController::StaticClass();
    HUDClass = ASBMenuHUD::StaticClass();
}