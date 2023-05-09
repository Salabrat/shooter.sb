// Salabrat Game, All rights Reserved. SB4
#pragma once

#include "UI/SBPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USBPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USBPlayerStatRowWidget::SetKills(const FText& Text)
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USBPlayerStatRowWidget::SetDeaths(const FText& Text)
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void USBPlayerStatRowWidget::SetTeam(const FText& Text)
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

void USBPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
