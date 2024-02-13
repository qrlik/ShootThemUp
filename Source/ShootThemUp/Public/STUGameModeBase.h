// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;

USTRUCT(BlueprintType)
struct FGameData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FLinearColor> TeamColors;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersAmount = 2;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "25"))
	int32 RoundsAmount = 4;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "300"))
	int32 RoundTime = 20;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "3", ClampMax = "30"))
	int32 RespawnTime = 5;
};

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	ASTUGameModeBase();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual void StartPlay() override;

	void Killed(const AController* KillerController, const AController* VictimController) const;
	void OnRespawn(AController* Controller);

	UFUNCTION(BlueprintCallable)
	const FGameData& GetGameData() const;
	float GetRoundRemainingTime() const;
	int32 GetCurrentRound() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData Data;

private:
	FLinearColor GetTeamColor(int32 TeamID) const;

	void CreateTeamsInfo() const;
	void SpawnBots();

	void GameOver() const;
	void StartRound();
	void EndRound();

	void SetPlayerColor(const AController* Controller) const;
	void SetRespawn(const AController* Controller, bool State) const;
	void ResetPlayer(AController* Controller);
	void ResetPlayers();

	void LogPlayerInfo() const;

	FTimerHandle RoundTimer;
	int32 CurrentRound = 0;
};
