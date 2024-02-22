// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget {
	GENERATED_BODY()

public:
	void SetPlayerIndicator(bool StateState) const;
	void SetPlayerName(const FText& Name) const;
	void SetKills(const FText& Kills) const;
	void SetDeaths(const FText& Deaths) const;
	void SetTeam(const FText& Team) const;
	void SetTeamColor(FLinearColor Color) const;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> PlayerIndicatorImage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KillsText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DeathsText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TeamText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> TeamImage;
};
