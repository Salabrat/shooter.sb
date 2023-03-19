// Salabrat Game, All rights Reserved. SB4


#include "Weapon/Components/SBWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


USBWeaponFXComponent::USBWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),//
		//ImpactData.NiagaraEffect,	
		Effect,//
		Hit.ImpactPoint,									//
		Hit.ImpactNormal.Rotation());
}
