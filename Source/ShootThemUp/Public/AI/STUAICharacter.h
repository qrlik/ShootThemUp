// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter {
	GENERATED_BODY()

public:
	ASTUAICharacter(const FObjectInitializer& Initializer);

	virtual void Tick(float DeltaSeconds) override;

	UBehaviorTree* GetBehaviorTree() const;

protected:
	virtual void BeginPlay() override;

	virtual void OnDeathImpl() override;
	virtual void OnHealthChangedImpl(float Delta) const override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	float HealthVisibilityDistance = 2000.f;

private:
	void UpdateHealthVisibility() const;
};
