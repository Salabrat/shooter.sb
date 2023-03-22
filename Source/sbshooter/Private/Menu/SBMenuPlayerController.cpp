// Salabrat Game, All rights Reserved. SB4


#include "Menu/SBMenuPlayerController.h"
#include "SBGameInstance.h"

void ASBMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
    GetWorld()->GetGameInstance<USBGameInstance>()->TestString = "Menu level says hello";
}
