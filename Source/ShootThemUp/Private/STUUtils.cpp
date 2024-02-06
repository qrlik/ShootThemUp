// Shoot Them Up Game. All Rights Reserved.

#include "STUUtils.h"

APawn* STUUtils::GetPawn(const AController* Controller) {
	if (Controller) {
		return Controller->GetPawn();
	}
	return nullptr;
}
