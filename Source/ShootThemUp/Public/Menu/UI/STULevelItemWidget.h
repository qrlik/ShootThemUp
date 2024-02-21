// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"

#include "STULevelItemWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

DECLARE_DELEGATE_OneParam(FOnLevelSelected, const FName&);

UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget {
	GENERATED_BODY()

public:
	const FLevelData& GetLevelData() const;
	void SetLevelData(const FLevelData& Data);
	void SetSelected(bool State) const;

	FOnLevelSelected OnLevelSelected;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LevelIconImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LevelFrameImage;

private:
	void InitLevelSelectButton();
	void InitLevelFrame() const;

	UFUNCTION()
	void OnLevelIconClicked();

	void UpdateLevelName() const;
	void UpdateLevelIcon() const;

	FLevelData LevelData;
};
