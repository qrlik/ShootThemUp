// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "MyEnvQueryTest_CanTakePickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API UMyEnvQueryTest_CanTakePickup : public UEnvQueryTest {
	GENERATED_BODY()

public:
	UMyEnvQueryTest_CanTakePickup(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
