// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent {
	GENERATED_BODY()

public:
	void StartRespawn(float Respawn);
	void Reset();

	float GetRespawnRemainingTime() const;
	bool IsActive() const;

private:
	void Respawn();

	FTimerHandle RespawnTimer;
};
