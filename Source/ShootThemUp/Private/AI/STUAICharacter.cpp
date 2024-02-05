// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAICharacter.h"

#include "AI/STUAIController.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent")) {
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();

	if (auto* Movement = GetCharacterMovement()) {
		Movement->bUseControllerDesiredRotation = true;
		bUseControllerRotationYaw = false;
	}
}

UBehaviorTree* ASTUAICharacter::GetBehaviorTree() const {
	return BehaviorTree;
}
