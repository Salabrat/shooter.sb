// Salabrat Game, All rights Reserved. SB4


#include "SBGameModeBase.h"
#include "Player/SBBaseCharacter.h"
#include "Player/SBPlayerController.h"
#include "UI/SBGameHUD.h"
#include "AIController.h"

ASBGameModeBase::ASBGameModeBase()
{
	DefaultPawnClass = ASBBaseCharacter::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
	HUDClass = ASBGameHUD::StaticClass();
}

void ASBGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
//	CreateTeamsInfo();
//	CurrentRound = 1;
//	StartRound();
}

UClass* ASBGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASBGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;
	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto SBAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
	RestartPlayer(SBAIController);
	}
}
