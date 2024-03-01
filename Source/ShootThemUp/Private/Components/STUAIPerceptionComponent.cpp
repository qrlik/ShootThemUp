// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetCurrentEnemy() const {
	const auto* Controller = Cast<AController>(GetOwner());
	if (!Controller) {
		return nullptr;
	}
	const auto* Pawn = Controller->GetPawn();
	if (!Pawn) {
		return nullptr;
	}

	AActor* Result = nullptr;
	float BestDistance = MAX_FLT;

	for (auto* Actor : GetPerceivedEnemies()) {
		if (const auto* Health = Actor->FindComponentByClass<USTUHealthComponent>(); !Health || Health->IsDead()) {
			continue;
		}
		if (!STUUtils::AreEnemies(Controller, STUUtils::GetController(Actor))) {
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

TArray<AActor*> USTUAIPerceptionComponent::GetPerceivedEnemies() const {
	if (const auto SightEnemies = GetPerceivedEnemiesBySense(UAISense_Sight::StaticClass()); !SightEnemies.IsEmpty()) {
		return SightEnemies;
	}
	return GetPerceivedEnemiesBySense(UAISense_Damage::StaticClass());
}

TArray<AActor*> USTUAIPerceptionComponent::GetPerceivedEnemiesBySense(TSubclassOf<UAISense> Sense) const {
	TArray<AActor*> PerceiveActors;
	const auto* Controller = Cast<AController>(GetOwner());

	GetCurrentlyPerceivedActors(Sense, PerceiveActors);
	PerceiveActors.RemoveAllSwap([Controller](const AActor* Actor) {
		return !STUUtils::AreEnemies(Controller, STUUtils::GetController(Actor));
	});
	return PerceiveActors;
}
