// Salabrat Game, All rights Reserved. SB4


#include "Weapon/SBLauncherWeapon.h"
#include "Weapon/SBProjectile.h"
//#include "Kismet/GameplayStatics.h"

void ASBLauncherWeapon::StartFire()
{
	MakeShot();
}

void ASBLauncherWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASBProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASBProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	//UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	DecreaseAmmo();
}
 