// Salabrat Game, All rights Reserved. SB4


#include "UI/SBGoToMenuWidget.h"
#include "Components/Button.h"
#include "SBGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBGoToMenuWidget, All, All);

void USBGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USBGoToMenuWidget::OnGoToMenu);
    }
}

void USBGoToMenuWidget::OnGoToMenu()    
{
    if (!GetWorld()) return;
    const auto SBGameInstance = GetWorld()->GetGameInstance<USBGameInstance>();
    if (!SBGameInstance) return;

    if (SBGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogSBGoToMenuWidget, Error, TEXT("Menu level name is NONE"));
        return;
    }
    UGameplayStatics::OpenLevel(this, SBGameInstance->GetMenuLevelName());
}