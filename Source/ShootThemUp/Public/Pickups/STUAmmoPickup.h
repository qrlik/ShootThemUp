// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup {
	GENERATED_BODY()

protected:
	virtual bool GiveTo(APawn* Pawn) const override;
};
