// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

enum class EMatchState;

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD {
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

private:
	void CreateWidgets();
	void InitMatchStateDelegate();

	void DrawCrossHair();

	void OnMatchStateChanged(EMatchState State);

	UPROPERTY()
	TMap<EMatchState, TObjectPtr<UUserWidget>> GameWidgets;
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentWidget;
};
