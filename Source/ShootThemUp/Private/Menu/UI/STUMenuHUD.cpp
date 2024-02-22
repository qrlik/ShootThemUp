// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STUMenuHUD.h"

#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay() {
	Super::BeginPlay();

	CreateMenuWidget();
}

void ASTUMenuHUD::CreateMenuWidget() const {
	if (auto* MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass)) {
		MenuWidget->AddToViewport();
		MenuWidget->Show();
	}
}
