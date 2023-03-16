// Salabrat Game, All rights Reserved. SB4


#include "Animations/SBEquipFinishedAnimNotify.h"

void USBEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
