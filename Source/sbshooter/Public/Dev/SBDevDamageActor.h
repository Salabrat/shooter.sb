// Salabrat Game, All rights Reserved. SB4

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBDevDamageActor.generated.h"

UCLASS()
class SBSHOOTER_API ASBDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBDevDamageActor();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float Radius = 300.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float Damage = 10.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool DoFullDamage = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
