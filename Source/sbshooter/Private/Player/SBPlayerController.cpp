// Salabrat Game, All rights Reserved. SB4


#include "Player/SBPlayerController.h"
#include "Components/SBRespawnComponent.h"
#include "SBGameModeBase.h"
#include "SBGameInstance.h"

ASBPlayerController::ASBPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USBRespawnComponent>("RespawnComponent");
}

void ASBPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    if (GetWorld())
    {
        if (const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASBPlayerController::OnMatchStateChanged);
        }
    }
}

void ASBPlayerController::OnMatchStateChanged(ESBMatchState State)
{
    if (State == ESBMatchState::InProgress)
    {
     SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
     SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASBPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}


void ASBPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASBPlayerController::OnPauseGame);
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASBPlayerController::OnMuteSound);
}

void ASBPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASBPlayerController::OnMuteSound()
{
    if (!GetWorld()) return;

    const auto SBGameInstace = GetWorld()->GetGameInstance<USBGameInstance>();
    if (!SBGameInstace) return;

    SBGameInstace->ToggleVolume();
}