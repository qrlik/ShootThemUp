// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUSpectatorWidget.h"

#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int& Time) const {
	const auto* RespawnComponent = STUUtils::GetComponentByClass<USTURespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsActive()) {
		return false;
	}
	Time = static_cast<int>(RespawnComponent->GetRespawnRemainingTime());
	return true;
}
