// Salabrat Game, All rights Reserved. SB4


#include "Weapon/Components/SBWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"


USBWeaponFXComponent::USBWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	//niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),//
		ImpactData.NiagaraEffect,							  //
		Hit.ImpactPoint,									  //
		Hit.ImpactNormal.Rotation());

	//decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
		ImpactData.DecalData.Material,										 //
		ImpactData.DecalData.Size,											 //
		Hit.ImpactPoint,													 //
		Hit.ImpactNormal.Rotation());										 //
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}
