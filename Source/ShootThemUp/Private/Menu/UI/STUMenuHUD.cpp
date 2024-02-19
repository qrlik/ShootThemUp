// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STUMenuHUD.h"

#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay() {
	Super::BeginPlay();

	CreateMenuWidget();
}

void ASTUMenuHUD::CreateMenuWidget() {
	if (auto* MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass)) {
		MenuWidget->AddToViewport();
	}
}
