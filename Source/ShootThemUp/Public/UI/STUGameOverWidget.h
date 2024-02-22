// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGameOverWidget.generated.h"

enum class EMatchState;
class UButton;
class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget {
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> PlayersStatBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ResetLevelButton;

private:
	void InitMatchStateDelegate();
	void InitResetLevelButton();

	void OnMatchStateChanged(EMatchState State);
	UFUNCTION()
	void OnResetLevel();

	void UpdatePlayersStat();
};
