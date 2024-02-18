// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameHUD.h"

#include "STUGameModeBase.h"
#include "STUUtils.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All);

void ASTUGameHUD::DrawHUD() {
	Super::DrawHUD();
	//DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() {
	Super::BeginPlay();
	CreateWidgets();
	InitMatchStateDelegate();
}

void ASTUGameHUD::CreateWidgets() {
	GameWidgets.Add(EMatchState::InProgress, CreateWidget(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EMatchState::Pause, CreateWidget(GetWorld(), PauseWidgetClass));
}

void ASTUGameHUD::InitMatchStateDelegate() {
	if (auto* GameMode = STUUtils::GetGameMode<ASTUGameModeBase>(GetWorld())) {
		check(!GameMode->OnMatchStateChange.IsBoundToObject(this));
		GameMode->OnMatchStateChange.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
	}
}

void ASTUGameHUD::DrawCrossHair() {
	constexpr auto HalfLine = 10.f;
	constexpr auto LineThickness = 2.f;
	const FLinearColor LineColor = FLinearColor::Green;
	const auto Center = FVector2D{ Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f };

	DrawLine(Center.X - HalfLine, Center.Y, Center.X + HalfLine, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X, Center.Y - HalfLine, Center.X, Center.Y + HalfLine, LineColor, LineThickness);
}

void ASTUGameHUD::OnMatchStateChanged(EMatchState State) {
	UE_LOG(LogGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
	const auto* It = GameWidgets.Find(State);
	if (!It) {
		return;
	}
	const auto Widget = *It;
	if (Widget == CurrentWidget) {
		return;
	}

	if (CurrentWidget) {
		CurrentWidget->RemoveFromParent();
	}
	Widget->AddToViewport();
	CurrentWidget = Widget;
}
