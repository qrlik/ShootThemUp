// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "AI/STUAIController.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent")) {
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUAIController::StaticClass();

	if (auto* Movement = GetCharacterMovement()) {
		Movement->bUseControllerDesiredRotation = true;
		bUseControllerRotationYaw = false;
	}
}

UBehaviorTree* ASTUAICharacter::GetBehaviorTree() const {
	return BehaviorTree;
}

void ASTUAICharacter::OnDeathImpl() {
	if (const auto* AIController = Cast<AAIController>(Controller)) {
		if (auto* Brain = AIController->GetBrainComponent()) {
			Brain->Cleanup();
		}
	}
}
