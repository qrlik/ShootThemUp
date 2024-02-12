// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;

USTRUCT(BlueprintType)
struct FGameData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersAmount = 2;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "25"))
	int32 RoundsAmount = 4;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "300"))
	int32 RoundTime = 20;
};

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	ASTUGameModeBase();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData Data;

private:
	void StartRound();
	void EndRound();

	void SpawnBots();

	FTimerHandle RoundTimer;
	int32 CurrentRound = 0;
};
