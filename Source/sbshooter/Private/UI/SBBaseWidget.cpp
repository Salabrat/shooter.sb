// Salabrat Game, All rights Reserved. SB4


#include "UI/SBBaseWidget.h"
//#include "Blueprint/UserWidget.h"
//#include "SBBaseWidget.generated.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"



void USBBaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
