// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTURespawnComponent;
class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController {
	GENERATED_BODY()

public:
	ASTUAIController();

	virtual void Tick(float DeltaTime) override;

	TWeakObjectPtr<AActor> GetEnemyActor() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USTURespawnComponent> Respawn;

private:
	void UpdateEnemyActor();
	void UpdateFocus();

	UPROPERTY()
	TObjectPtr<USTUAIPerceptionComponent> Perception;

	TWeakObjectPtr<AActor> EnemyActor;
};
