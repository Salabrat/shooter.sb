// Salabrat Game, All rights Reserved. SB4


#include "UI/SBPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void USBPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USBPauseWidget::OnClearPause);
    }
}

void USBPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
