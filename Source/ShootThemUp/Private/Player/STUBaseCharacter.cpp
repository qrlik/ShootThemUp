// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName)) {
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTUBaseCharacter::BeginPlay() {
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(HealthComponent.Get(), &USTUHealthComponent::OnTakeAnyDamage);
	HealthComponent->OnHealthChange.BindUObject(this, &ASTUBaseCharacter::UpdateHealthText);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);

	UpdateHealthText();
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::StopRun);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
}

float ASTUBaseCharacter::GetDirectionAngle() const {
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	if (VelocityNormal.IsZero()) {
		return 0.f;
	}
	const auto Forward = GetActorForwardVector();
	const auto Angle = FMath::Acos(Forward.Dot(VelocityNormal));
	const auto Degrees = FMath::RadiansToDegrees(Angle);
	const auto Cross = Forward.Cross(VelocityNormal);
	return (FMath::IsNearlyZero(Cross.Z)) ? Degrees : Degrees * FMath::Sign(Cross.Z);
}

void ASTUBaseCharacter::OnDeath() {
	PlayAnimMontage(DeathAnimMontage);
	if (auto* MovementComponent = GetCharacterMovement()) {
		MovementComponent->DisableMovement();
	}
	if (Controller) {
		Controller->ChangeState(NAME_Spectating);
	}
	SetLifeSpan(5.f);
}

void ASTUBaseCharacter::MoveForward(float Amount) {
	if (!FMath::IsNearlyZero(Amount)) {
		AddMovementInput(GetActorForwardVector(), Amount);
	}
	UpdateMovementFlag(EMovementFlags::MoveForward, (Amount > 0.f) ? Amount : 0.f);
}

void ASTUBaseCharacter::MoveRight(float Amount) {
	if (!FMath::IsNearlyZero(Amount)) {
		AddMovementInput(GetActorRightVector(), Amount);
	}
	UpdateMovementFlag(EMovementFlags::MoveSide, Amount);
}

void ASTUBaseCharacter::StartRun() {
	UpdateMovementFlag(EMovementFlags::AbleToRun, 1.f);
}

void ASTUBaseCharacter::StopRun() {
	UpdateMovementFlag(EMovementFlags::AbleToRun, 0.f);
}

void ASTUBaseCharacter::UpdateMovementFlag(EMovementFlags Flag, float Amount) const {
	if (auto* MovementComponent = FindComponentByClass<USTUCharacterMovementComponent>()) {
		if (FMath::IsNearlyEqual(Amount, 0.f)) {
			MovementComponent->RemoveMovementFlag(Flag);
		}
		else {
			MovementComponent->AddMovementFlag(Flag);
		}
	}
}

void ASTUBaseCharacter::UpdateHealthText() const {
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), HealthComponent->GetHealth())));
}
