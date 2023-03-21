// Salabrat Game, All rights Reserved. SB4


#include "SBGameModeBase.h"
#include "Player/SBBaseCharacter.h"
#include "Player/SBPlayerController.h"
#include "UI/SBGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBGameModeBase, All, All);

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
	//CreateTeamsInfo();
	CurrentRound = 1;
	StartRound();
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

void ASBGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASBGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASBGameModeBase::GameTimerUpdate()
{

	UE_LOG(LogSBGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogSBGameModeBase, Display, TEXT("------------GameOver();-----------"));
		}
	}
}

void ASBGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASBGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	//SetPlayerColor(Controller);
}


