// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

struct FLevelData;
class UButton;
class UHorizontalBox;
class USTULevelItemWidget;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget {
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LevelItemsBox;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HideAnimation;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<USoundCue> StartGameSound;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;

private:
	void InitStartGameButton();
	void InitQuitGameButton();
	void InitLevelItemsBox();

	void OnHideAnimationFinished();

	UFUNCTION()
	void OnStartGame();
	UFUNCTION()
	void OnQuitGame();
	void OnLevelSelected(const FName& LevelName);

	void SelectLevel(TObjectPtr<USTULevelItemWidget> LevelWidget);

	UPROPERTY()
	TArray<TObjectPtr<USTULevelItemWidget>> LevelItemWidgets;
	UPROPERTY()
	TObjectPtr<USTULevelItemWidget> SelectedLevelItemWidget;
};
