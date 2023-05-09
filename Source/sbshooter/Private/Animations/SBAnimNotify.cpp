// Salabrat Game, All rights Reserved. SB4


#include "Animations/SBAnimNotify.h"

void USBAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
