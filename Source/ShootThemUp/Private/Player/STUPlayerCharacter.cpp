// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& Initializer):
	Super(Initializer) {
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::StopRun);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent.Get(), &USTUWeaponComponent::Reload);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent.Get(), &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAxis("Fire", WeaponComponent.Get(), &USTUWeaponComponent::OnFire);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
}

void ASTUPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	
	check(SpringArmComponent);
	check(CameraComponent);
}

void ASTUPlayerCharacter::OnDeathImpl() {
	if (Controller) {
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTUPlayerCharacter::OnHealthChangedImpl(float Delta) const {
	if (Delta < 0.f) {
		PlayCameraShake();
	}
}

void ASTUPlayerCharacter::MoveForward(float Amount) {
	if (!FMath::IsNearlyZero(Amount)) {
		AddMovementInput(GetActorForwardVector(), Amount);
	}
	UpdateMovementFlag(EMovementFlags::MoveForward, (Amount > 0.f) ? Amount : 0.f);
}

void ASTUPlayerCharacter::MoveRight(float Amount) {
	if (!FMath::IsNearlyZero(Amount)) {
		AddMovementInput(GetActorRightVector(), Amount);
	}
	UpdateMovementFlag(EMovementFlags::MoveSide, Amount);
}

void ASTUPlayerCharacter::PlayCameraShake() const {
	if (const auto* PController = GetController<APlayerController>(); PController && PController->PlayerCameraManager) {
		PController->PlayerCameraManager->StartCameraShake(CameraShake);
	}
}
