// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState {
	GENERATED_BODY()

public:
	FLinearColor GetTeamColor() const;
	int32 GetTeamID() const;
	int32 GetKills() const;
	int32 GetDeaths() const;

	void OnKill();
	void OnDeath();
	void SetTeamColor(FLinearColor Color);
	void SetTeamID(int32 Team);

	void Log() const;

private:
	FLinearColor TeamColor;
	int32 TeamID = 0;

	int32 KillsAmount = 0;
	int32 DeathAmount = 0;
};
