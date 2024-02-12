// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAIController.h"

#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController() {
	Perception = CreateDefaultSubobject<USTUAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*Perception);

	bWantsPlayerState = true;
}

void ASTUAIController::Tick(float DeltaTime) {
	UpdateEnemyActor();
	UpdateFocus();
	Super::Tick(DeltaTime);
}

TWeakObjectPtr<AActor> ASTUAIController::GetEnemyActor() const {
	return EnemyActor;
}

void ASTUAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (const auto* AICharacter = Cast<ASTUAICharacter>(InPawn)) {
		RunBehaviorTree(AICharacter->GetBehaviorTree());
	}
}

void ASTUAIController::UpdateEnemyActor() {
	EnemyActor = Perception->GetClosestEnemy();
}

void ASTUAIController::UpdateFocus() {
	SetFocus(EnemyActor.Get());
}
