// Salabrat Game, All rights Reserved. SB4


#include "Weapon/Components/SBWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"


USBWeaponFXComponent::USBWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),//
		//ImpactData.NiagaraEffect,	
		Effect,//
		Hit.ImpactPoint,									//
		Hit.ImpactNormal.Rotation());
}
