// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

struct FLevelData;

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	const TArray<FLevelData>& GetLevelsData() const;
	const FName& GetLastLevelName() const;
	const FName& GetMenuLevelName() const;

	void LoadLevel(const FName& Level);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Levels Data with unique names"))
	TArray<FLevelData> LevelsData;

private:
	FName LastLevelName = NAME_None;
};
