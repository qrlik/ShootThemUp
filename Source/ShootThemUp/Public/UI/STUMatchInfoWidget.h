// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMatchInfoWidget.generated.h"

class ASTUGameModeBase;

UCLASS()
class SHOOTTHEMUP_API USTUMatchInfoWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FIntPoint GetRoundsInfo() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetRemainingTime() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKills() const;
};
