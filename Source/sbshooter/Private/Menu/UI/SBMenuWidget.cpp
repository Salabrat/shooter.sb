// Salabrat Game, All rights Reserved. SB4


#include "Menu/UI/SBMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SBGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBMenuWidget, All, All);

void USBMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USBMenuWidget::OnStartGame);
    }
    
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USBMenuWidget::OnQuitGame);
    }

  //  InitLevelItems();
}

void USBMenuWidget::OnStartGame()
{
    if (!GetWorld()) return;

    const auto SBGameInstance = GetWorld()->GetGameInstance<USBGameInstance>();
    if (!SBGameInstance) return;

    if(SBGameInstance->GetStartupLevelName().IsNone())
    {

        return;
    }

   // SBGameInstance->SetStartupLevelData(Data);
   // PlayAnimation(HideAnimation);
    const FName StartupLevelName = "sbMap";
    UGameplayStatics::OpenLevel(this,SBGameInstance->GetStartupLevelName());
}

void USBMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
