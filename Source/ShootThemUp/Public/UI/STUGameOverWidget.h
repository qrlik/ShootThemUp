// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameOverWidget.generated.h"

enum class EMatchState;
class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget {
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> PlayersStatBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowClass;

private:
	void InitMatchStateDelegate();

	void OnMatchStateChanged(EMatchState State);
	void UpdatePlayersStat();
};
