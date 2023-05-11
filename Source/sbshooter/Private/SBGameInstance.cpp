// Salabrat Game, All rights Reserved. SB4


#include "SBGameInstance.h"
#include "Sound/SBSoundFuncLib.h"

void USBGameInstance::ToggleVolume()
{
    USBSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}