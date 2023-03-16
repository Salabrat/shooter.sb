// Salabrat Game, All rights Reserved. SB4


#include "Weapon/SBLauncherWeapon.h"
#include "Weapon/SBProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASBLauncherWeapon::StartFire()
{
	MakeShot();
}

void ASBLauncherWeapon::MakeShot()
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);

	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
