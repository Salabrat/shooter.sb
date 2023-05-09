// Salabrat Game, All rights Reserved. SB4


#include "UI/SBHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USBHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar) return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))  //
        ? ESlateVisibility::Hidden
        : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}
