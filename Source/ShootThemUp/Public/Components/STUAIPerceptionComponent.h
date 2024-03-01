// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STUAIPerceptionComponent.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUAIPerceptionComponent : public UAIPerceptionComponent {
	GENERATED_BODY()

public:
	AActor* GetCurrentEnemy() const;

private:
	TArray<AActor*> GetPerceivedEnemies() const;
	TArray<AActor*> GetPerceivedEnemiesBySense(TSubclassOf<UAISense> Sense) const;
};
