// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUHealthBarWidget : public UUserWidget {
	GENERATED_BODY()

public:
	void SetHealthPercent(float Percent) const;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float PercentVisibilityThreshold = 0.8f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor DefaultColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor LowColor = FLinearColor::Red;
};
