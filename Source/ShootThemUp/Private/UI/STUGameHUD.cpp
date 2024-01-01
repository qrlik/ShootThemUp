// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameHUD.h"

#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD() {
	Super::DrawHUD();
	DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair() {
	constexpr auto HalfLine = 10.f;
	constexpr auto LineThickness = 2.f;
	const FLinearColor LineColor = FLinearColor::Green;
	const auto Center = FVector2D{ Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f };

	DrawLine(Center.X - HalfLine, Center.Y, Center.X + HalfLine, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X, Center.Y - HalfLine, Center.X, Center.Y + HalfLine, LineColor, LineThickness);
}
