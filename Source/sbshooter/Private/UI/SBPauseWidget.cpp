// Salabrat Game, All rights Reserved. SB4


#include "UI/SBPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool USBPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USBPauseWidget::OnClearPause);
    }

    return InitStatus;
}

void USBPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
