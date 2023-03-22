// Salabrat Game, All rights Reserved. SB4


#include "Menu/UI/SBMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetSystemLibrary.h"

void USBMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USBMenuWidget::OnStartGame);
    }
    /*
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }

    InitLevelItems();*/
}

void USBMenuWidget::OnStartGame()
{
   // PlayAnimation(HideAnimation);
    const FName StartupLevelName = "sbMap";
    UGameplayStatics::OpenLevel(this,StartupLevelName);
}