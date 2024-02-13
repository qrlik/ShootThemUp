// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerController.h"

#include "Components/STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController() {
	Respawn = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::OnPossess(APawn* aPawn) {
	Super::OnPossess(aPawn);

	OnPawnPossess.Broadcast();
}
