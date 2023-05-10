// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBRiffleWeapon.generated.h"

class USBWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;
class USoundCue;

UCLASS()
class SBSHOOTER_API ASBRiffleWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	ASBRiffleWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
			float TimeBetweenShots = 0.1f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
			float DamageAmount = 10.0f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
			float BulletSpread = 1.5f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
			UNiagaraSystem* TraceFX;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
			FString TraceTargetName = "TraceTarget";

		UPROPERTY(VisibleAnywhere, Category = "VFX")
			USBWeaponFXComponent* WeaponFXComponent;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
			USoundCue* NoAmmoSound;

		virtual	void BeginPlay() override;
		virtual	void MakeShot();
		virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;
	
	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void MakeDamage(const FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visible);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

	AController* GetController() const; 
};
