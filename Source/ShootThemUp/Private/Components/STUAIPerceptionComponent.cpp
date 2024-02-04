// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const {
	const auto* Pawn = GetOwnerPawn();
	if (!Pawn) {
		return nullptr;
	}

	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.IsEmpty()) {
		return nullptr;
	}
	AActor* Result = nullptr;
	float BestDistance = MAX_FLT;
	for (auto* Actor : PerceiveActors) {
		if (const auto* Health = Actor->FindComponentByClass<USTUHealthComponent>(); !Health || Health->IsDead()) {
			continue;
		}
		const auto Distance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Length();
		if (Distance < BestDistance) {
			BestDistance = Distance;
			Result = Actor;
		}
	}
	return Result;
}

APawn* USTUAIPerceptionComponent::GetOwnerPawn() const {
	const auto* Controller = Cast<AAIController>(GetOwner());
	if (!Controller) {
		return nullptr;
	}
	return Controller->GetPawn();
}
