// Salabrat Game, All rights Reserved. SB4


#include "Player/SBPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBPlayerState, All, All);

void ASBPlayerState::LogInfo()
{
	UE_LOG(LogSBPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths %i"), TeamID, KillsNum, DeathsNum);
}
