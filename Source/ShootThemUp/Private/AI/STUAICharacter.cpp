// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAICharacter.h"

#include "AI/STUAIController.h"
#include "BrainComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/STUHealthBarWidget.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent")) {
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUAIController::StaticClass();

	if (auto* Movement = GetCharacterMovement()) {
		Movement->bUseControllerDesiredRotation = true;
		bUseControllerRotationYaw = false;
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	UpdateHealthVisibility();
}

UBehaviorTree* ASTUAICharacter::GetBehaviorTree() const {
	return BehaviorTree;
}

void ASTUAICharacter::BeginPlay() {
	Super::BeginPlay();
	check(HealthWidgetComponent);
}

void ASTUAICharacter::OnDeathImpl() {
	if (const auto* AIController = Cast<AAIController>(Controller)) {
		if (auto* Brain = AIController->GetBrainComponent()) {
			Brain->Cleanup();
		}
	}
}

void ASTUAICharacter::OnHealthChangedImpl(float Delta) const {
	if (const auto* HealthWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetWidget())) {
		HealthWidget->SetHealthPercent(HealthComponent->GetHealthPercent() / 100.f);
	}
}

void ASTUAICharacter::UpdateHealthVisibility() const {
	const auto* World = GetWorld();
	if (!World) {
		return;
	}
	const auto* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) {
		return;
	}
	if (const auto* Player = PlayerController->GetPawnOrSpectator()) {
		const auto Distance = FVector::Distance(Player->GetActorLocation(), GetActorLocation());
		HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
	}
}
