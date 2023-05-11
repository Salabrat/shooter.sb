// Salabrat Game, All rights Reserved. SB4


#include "Components/SBHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "SBGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USBHealthComponent::USBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth (MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USBHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &USBHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USBHealthComponent::OnTakeRadialDamage);
	}
}

void USBHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
	class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType,
	AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	 UE_LOG(LogHealthComponent, Display, TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage, FinalDamage, *BoneName.ToString());
	ApplyDamage(FinalDamage, InstigatedBy);
}

void USBHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin,
	FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser)
{
	 UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
	ApplyDamage(Damage, InstigatedBy);
}

void USBHealthComponent::OnTakeAnyDamage
(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
	AActor* DamageCauser)
{
	// UE_LOG(LogHealthComponent, Display, TEXT("On any damage: %f"), Damage);
}

void USBHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USBHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
	//ReportDamageEvent(Damage, InstigatedBy);
}

void USBHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USBHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool USBHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

bool USBHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);

}
void USBHealthComponent::PlayCameraShake() 
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USBHealthComponent::Killed(AController* KillerController)//, AController* VictimController)
{

	if (!GetWorld()) return;

	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);


	/*const auto KillerPlayerState = KillerController ? Cast <ASBPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast <ASBPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	StartRespawn(VictimController);*/
}

float USBHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if (!Character ||             //
		!Character->GetMesh() ||  //
		!Character->GetMesh()->GetBodyInstance(BoneName))
		return 1.0f;

	const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial)) return 1.0f;

	return DamageModifiers[PhysMaterial];
}
