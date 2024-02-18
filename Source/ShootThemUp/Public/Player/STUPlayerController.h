// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

enum class EMatchState;
class USTURespawnComponent;

DECLARE_MULTICAST_DELEGATE(FPawnPossessSignature);

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	ASTUPlayerController();

	FPawnPossessSignature OnPawnPossess;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USTURespawnComponent> Respawn;

private:
	void InitMatchStateDelegate();

	void OnMatchStateChanged(EMatchState State);
	void OnPauseGame();
};
