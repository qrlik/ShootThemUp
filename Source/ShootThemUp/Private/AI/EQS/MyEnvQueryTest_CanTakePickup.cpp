// Shoot Them Up Game. All Rights Reserved.

#include "AI/EQS/MyEnvQueryTest_CanTakePickup.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Pickups/STUBasePickup.h"

UMyEnvQueryTest_CanTakePickup::UMyEnvQueryTest_CanTakePickup(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer) {
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();
	SetWorkOnFloatValues(false);
}

void UMyEnvQueryTest_CanTakePickup::RunTest(FEnvQueryInstance& QueryInstance) const {
	const auto* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool WantsBeTaken = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It) {
		const auto* ItemPickup = Cast<ASTUBasePickup>(GetItemActor(QueryInstance, It.GetIndex()));
		if (!ItemPickup) {
			continue;
		}
		It.SetScore(TestPurpose, FilterType, ItemPickup->IsActive(), WantsBeTaken);
	}
}
