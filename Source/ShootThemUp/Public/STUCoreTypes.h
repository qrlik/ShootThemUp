#pragma once

#include "STUCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FLevelData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName LevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly)
	FName LevelDisplayName = NAME_None;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> LevelIcon;
};
