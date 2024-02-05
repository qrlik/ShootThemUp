// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter {
	GENERATED_BODY()

public:
	ASTUAICharacter(const FObjectInitializer& Initializer);

	UBehaviorTree* GetBehaviorTree() const;

protected:
	virtual void OnDeathImpl() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
