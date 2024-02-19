// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

private:
	void InitStartGameButton();

	UFUNCTION()
	void OnStartGame();
};
