// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBRiffleWeapon.generated.h"

UCLASS()
class SBSHOOTER_API ASBRiffleWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
			float TimeBetweenShots = 0.1f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
			float BulletSpread = 1.5f;
		virtual	void MakeShot();
		virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;

};
