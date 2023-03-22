// Salabrat Game, All rights Reserved. SB4


#include "UI/SBGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "SBGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBGameHUD, All, All);

void ASBGameHUD::DrawHUD()
{
	Super::DrawHUD();
	//DrawCrossHair();
}

void ASBGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASBGameHUD::OnMatchStateChanged);
		}
	}
}

void ASBGameHUD::OnMatchStateChanged(ESBMatchState State)
{
	UE_LOG(LogSBGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));

}

void ASBGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

