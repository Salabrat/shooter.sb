// Salabrat Game, All rights Reserved. SB4


#include "AI/SBAIController.h"
#include "AI/SBAICharacter.h"
#include "Components/SBAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASBAIController::ASBAIController()
{
	SBAIPerceptionComponent = CreateDefaultSubobject<USBAIPerceptionComponent>("SBAIPerceptionComponent");
	SetPerceptionComponent(*SBAIPerceptionComponent);

	/*RespawnComponent = CreateDefaultSubobject<USBRespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;*/
}

void ASBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SBCharacter = Cast<ASBAICharacter>(InPawn);
	if (SBCharacter)
	{
		RunBehaviorTree(SBCharacter->UBehaviorTreeAsset);
	}
}

void ASBAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}
AActor* ASBAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}