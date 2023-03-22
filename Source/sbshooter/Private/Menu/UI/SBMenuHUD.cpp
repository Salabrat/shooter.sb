// Salabrat Game, All rights Reserved. SB4


#include "Menu/UI/SBMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASBMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
          if (MenuWidget)
        { 
        MenuWidget->AddToViewport();
      //  MenuWidget->Show();
        }
    }
}
