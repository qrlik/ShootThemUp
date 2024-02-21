// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

struct FLevelData;
class USTULevelItemWidget;
class UHorizontalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LevelItemsBox;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;

private:
	void InitStartGameButton();
	void InitQuitGameButton();
	void InitLevelItemsBox();

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
