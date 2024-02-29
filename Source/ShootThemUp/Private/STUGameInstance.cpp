// Shoot Them Up Game. All Rights Reserved.

#include "STUGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/STUSoundFuncLib.h"
#include "STUCoreTypes.h"

DEFINE_LOG_CATEGORY_STATIC(STUGameInstance, All, All);

const TArray<FLevelData>& USTUGameInstance::GetLevelsData() const {
	return LevelsData;
}

const FName& USTUGameInstance::GetLastLevelName() const {
	return LastLevelName;
}

const FName& USTUGameInstance::GetMenuLevelName() const {
	return MenuLevelName;
}

void USTUGameInstance::LoadLevel(const FName& Level) {
	for (const auto& LevelData : LevelsData) {
		if (Level == LevelData.LevelName) {
			LastLevelName = Level;
			UGameplayStatics::OpenLevel(this, Level);
			return;
		}
	}
	UE_LOG(STUGameInstance, Error, TEXT("Can't find level - %s"), *Level.ToString());
}

void USTUGameInstance::ToggleVolume() const {
	USTUSoundFuncLib::ToggleSoundClass(MasterSoundClass);
}
