// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName)) {
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

void ASTUBaseCharacter::BeginPlay() {
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(SpringArmComponent);
	check(CameraComponent);
	check(WeaponComponent);

	OnTakeAnyDamage.AddDynamic(HealthComponent.Get(), &USTUHealthComponent::OnTakeAnyDamage);
	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
	HealthComponent->OnHealthChange.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);

	UpdateHealthText();
}

void ASTUBaseCharacter::OnDeathImpl() {
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::StopRun);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent.Get(), &USTUWeaponComponent::Reload);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent.Get(), &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAxis("Fire", WeaponComponent.Get(), &USTUWeaponComponent::OnFire);
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

USTUHealthComponent* ASTUBaseCharacter::GetHealthComponent() const {
	return HealthComponent;
}

USTUWeaponComponent* ASTUBaseCharacter::GetWeaponComponent() const {
	return WeaponComponent;
}

void ASTUBaseCharacter::OnDeath() {
	//PlayAnimMontage(DeathAnimMontage);
	OnDeathImpl();

	if (auto* MovementComponent = GetCharacterMovement()) {
		MovementComponent->DisableMovement();
	}
	if (auto* Capsule = GetCapsuleComponent()) {
		Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
	if (Controller) {
		Controller->ChangeState(NAME_Spectating);
	}
	SetLifeSpan(LifeSpanOnDeath);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTUBaseCharacter::OnHealthChanged(float Delta) const {
	if (Delta < 0.f) {
		PlayCameraShake();
	}
	UpdateHealthText();
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) {
	const auto FallVelocity = -GetVelocity().Z;
	if (FallVelocity < 0.f || FallVelocity < LandedDamageVelocity.X) {
		return;
	}
	const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocity);
	TakeDamage(FallDamage, FDamageEvent{}, nullptr, nullptr);
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

void ASTUBaseCharacter::PlayCameraShake() const {
	if (const auto* PController = GetController<APlayerController>(); PController && PController->PlayerCameraManager) {
		PController->PlayerCameraManager->StartCameraShake(CameraShake);
	}
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
