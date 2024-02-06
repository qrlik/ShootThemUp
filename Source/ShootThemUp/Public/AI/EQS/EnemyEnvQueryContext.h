// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnemyEnvQueryContext.generated.h"

UCLASS()
class SHOOTTHEMUP_API UEnemyEnvQueryContext : public UEnvQueryContext {
	GENERATED_BODY()

public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FName EnemyActorKey = "EnemyActor";
};
