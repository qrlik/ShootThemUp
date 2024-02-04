// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAIController.h"

#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController() {
	Perception = CreateDefaultSubobject<USTUAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*Perception);
}

void ASTUAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	SetFocus(Perception->GetClosestEnemy());
}

void ASTUAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (const auto* AICharacter = Cast<ASTUAICharacter>(InPawn)) {
		RunBehaviorTree(AICharacter->GetBehaviorTree());
	}
}
