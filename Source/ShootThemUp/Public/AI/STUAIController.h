// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

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
	TObjectPtr<USTUAIPerceptionComponent> Perception;

private:
	void UpdateEnemyActor();
	void UpdateFocus();

	TWeakObjectPtr<AActor> EnemyActor;
};
