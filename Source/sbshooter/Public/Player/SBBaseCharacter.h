// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USBHealthComponent;
class UTextRenderComponent;
class USBWeaponComponent;

UCLASS()
class SBSHOOTER_API ASBBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBBaseCharacter(const FObjectInitializer& ObjInit);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USBHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USBWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(10.0f, 100.0f);


	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float	GetMovementDirection() const;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	void OnDeath();
	void OnHealthChanged(float Health);
	
	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

};


