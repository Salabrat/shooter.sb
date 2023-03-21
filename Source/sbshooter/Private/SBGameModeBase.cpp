// Salabrat Game, All rights Reserved. SB4


#include "SBGameModeBase.h"
#include "Player/SBBaseCharacter.h"
#include "Player/SBPlayerController.h"
#include "UI/SBGameHUD.h"
#include "AIController.h"
#include "Player/SBPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBGameModeBase, All, All);

ASBGameModeBase::ASBGameModeBase()
{
	DefaultPawnClass = ASBBaseCharacter::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
	HUDClass = ASBGameHUD::StaticClass();
	PlayerStateClass = ASBPlayerState::StaticClass();
}

void ASBGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

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
			LogPlayerInfo();
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

void ASBGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)continue;

		const auto PlayerState = Cast<ASBPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASBGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogSBGameModeBase, Warning, TEXT("NoColorForTeam ID: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void ASBGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASBBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<ASBPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASBGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
const auto KillerPlayerState = KillerController ? Cast <ASBPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast <ASBPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	//StartRespawn(VictimController);
}

void ASBGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)continue;

		const auto PlayerState = Cast<ASBPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}

}
