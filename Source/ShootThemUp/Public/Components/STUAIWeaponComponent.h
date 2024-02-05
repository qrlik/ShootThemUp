// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUAIWeaponComponent : public USTUWeaponComponent {
	GENERATED_BODY()

protected:
	virtual void OnEmptyClipImpl() override;
	virtual void OnReloadFinishedImpl() override;

private:
	bool bChangeWeaponAfterReload = false;
};
