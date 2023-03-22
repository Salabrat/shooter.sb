// Salabrat Game, All rights Reserved. SB4


#include "UI/SBGameOverWidget.h"
#include "SBGameModeBase.h"
#include "Player/SBPlayerState.h"
#include "UI/SBPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "SBUtils.h"

bool USBGameOverWidget::Initialize()
{
    if (GetWorld())
    {
        const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USBGameOverWidget::OnMatchStateChanged);
        }
    }
    return Super::Initialize();
}

void USBGameOverWidget::OnMatchStateChanged(ESBMatchState State)
{
    if (State == ESBMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USBGameOverWidget::UpdatePlayersStat()
{
    if (!GetWorld() || !PlayerStatBox) return;

   PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASBPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<USBPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(SBUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(SBUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRowWidget->SetTeam(SBUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
       // PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}
