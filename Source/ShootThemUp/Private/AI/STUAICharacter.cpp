// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAICharacter.h"

#include "AI/STUAIController.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& Initializer):
	Super(Initializer) {
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();
}
