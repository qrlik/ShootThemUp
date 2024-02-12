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

	void SetTeamColor(FLinearColor Color);
	void SetTeamID(int32 Team);

private:
	FLinearColor TeamColor;
	int32 TeamID = 0;
};
