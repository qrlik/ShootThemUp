// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;

DECLARE_MULTICAST_DELEGATE(FPawnPossessSignature);

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	ASTUPlayerController();

	FPawnPossessSignature OnPawnPossess;

protected:
	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USTURespawnComponent> Respawn;
};
