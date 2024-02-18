// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameHUD.h"

#include "STUGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All);

void ASTUGameHUD::DrawHUD() {
	Super::DrawHUD();
	//DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() {
	Super::BeginPlay();
	if (auto* PlayerHUDWidget = CreateWidget(GetWorld(), PlayerHUDWidgetClass)) {
		PlayerHUDWidget->AddToViewport();
	}
	InitStateDelegate();
}

void ASTUGameHUD::InitStateDelegate() {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}
	if (auto* GameMode = World->GetAuthGameMode<ASTUGameModeBase>()) {
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
}
