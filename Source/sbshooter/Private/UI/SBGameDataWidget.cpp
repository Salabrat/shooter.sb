// Salabrat Game, All rights Reserved. SB4


#include "UI/SBGameDataWidget.h"
#include "SBGameModeBase.h"
#include "Player/SBPlayerState.h"

int32 USBGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetSBPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USBGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetSBGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USBGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSBGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}
int32 USBGameDataWidget::GetRoundSecodsRemaining() const
{
	const auto GameMode = GetSBGameMode();
	return GameMode ? GameMode->GetRoundSecodsRemaining() : 0;
}

ASBGameModeBase* USBGameDataWidget::GetSBGameMode() const
{
	return GetWorld() ? Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASBPlayerState* USBGameDataWidget::GetSBPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASBPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
