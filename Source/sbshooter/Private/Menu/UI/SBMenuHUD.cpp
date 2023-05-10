// Salabrat Game, All rights Reserved. SB4


#include "Menu/UI/SBMenuHUD.h"
#include "UI/SBBaseWidget.h"

void ASBMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<USBBaseWidget>(GetWorld(), MenuWidgetClass);
          if (MenuWidget)
        { 
        MenuWidget->AddToViewport();
        MenuWidget->Show();
        }
    }
}
