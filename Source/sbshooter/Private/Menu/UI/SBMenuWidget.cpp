
// Salabrat Game, All rights Reserved. SB4

#include "Menu/UI/SBMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SBGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/SBLevelItemWidget.h"

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

  InitLevelItems();
}

void USBMenuWidget::InitLevelItems()
{
    const auto SBGameInstance = GetSBGameInstance();
    if (!SBGameInstance) return;

    checkf(SBGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

   if (!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : SBGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USBLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USBMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

   if (SBGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(SBGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(SBGameInstance->GetStartupLevel());
    }
}

void USBMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto SBGameInstance = GetSBGameInstance();
    if (!SBGameInstance) return;

    SBGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void USBMenuWidget::OnStartGame()
{
//   if (!GetWorld()) return;
    PlayAnimation(HideAnimation);
    //const auto SBGameInstance = GetSBGameInstance();//GetWorld()->GetGameInstance<USBGameInstance>();
  //  if (!SBGameInstance) return;

   /* if(SBGameInstance->GetStartupLevelName().IsNone())
    {

        return;
    }

    */
   // SBGameInstance->SetStartupLevelData(Data);
   // 
  //  const FName StartupLevelName = "sbMap";
   // UGameplayStatics::OpenLevel(this,SBGameInstance->GetStartupLevel().LevelName);
}

void USBMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation != HideAnimation) return;

    const auto SBGameInstance = GetSBGameInstance();
    if (!SBGameInstance) return;

    UGameplayStatics::OpenLevel(this, SBGameInstance->GetStartupLevel().LevelName);
}

void USBMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USBGameInstance* USBMenuWidget::GetSBGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USBGameInstance>();
}
