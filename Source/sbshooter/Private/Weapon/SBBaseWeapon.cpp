// Salabrat Game, All rights Reserved. SB4


#include "Weapon/SBBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASBBaseWeapon::ASBBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASBBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("BULLETS ne mozhet byt' menshe null"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips ne mozhet byt' menshe null"));
	CurrentAmmo = DefaultAmmo;
}

void ASBBaseWeapon::StartFire(){}

void ASBBaseWeapon::StopFire(){}

void ASBBaseWeapon::MakeShot(){}

bool ASBBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto SBCharacter = Cast<ACharacter>(GetOwner());
	if (!SBCharacter) return false;

	if (SBCharacter->IsPlayerControlled())
	{
		const auto Controller = SBCharacter->GetController<APlayerController>();
		if (!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector ASBBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASBBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASBBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASBBaseWeapon::DecreaseAmmo() 
{
	if (CurrentAmmo.Bullets == 0)
	{
		//UE_LOG(LogBaseWeapon, Warning, TEXT("Clip Is Empty"));
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		OnClipEmpty.Broadcast(this);
	}
}

bool ASBBaseWeapon::IsAmmoEmpty() const 
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASBBaseWeapon::IsClipEmpty() const 
{
	return CurrentAmmo.Bullets == 0;
}

void ASBBaseWeapon::ChangeClip() 
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Display, TEXT("nomoreclipsSBSB"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	//UE_LOG(LogBaseWeapon, Display, TEXT("ReloadClipsSBSB"));
}

bool ASBBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets&& CurrentAmmo.Clips > 0;
}

void ASBBaseWeapon::LogAmmo() 
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool ASBBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && //
		CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASBBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

	if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
			UE_LOG(LogBaseWeapon, Display, TEXT("Clips ADDED"));
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOG(LogBaseWeapon, Display, TEXT("Ammo is full now"));
		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		UE_LOG(LogBaseWeapon, Display, TEXT("Bullets ADDED"));
	}

	return true;
}

UNiagaraComponent* ASBBaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, //
		WeaponMesh,//
		MuzzleSocketName,//
		FVector::ZeroVector,//
		FRotator::ZeroRotator,//
		EAttachLocation::SnapToTarget, true);
}