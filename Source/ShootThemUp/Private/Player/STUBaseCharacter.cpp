// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& Initializer):
	Super(Initializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName)) {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTUBaseCharacter::InitMovementComponent() {
	MovementComponent = Cast<USTUCharacterMovementComponent>(GetMovementComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay() {
	Super::BeginPlay();
	InitMovementComponent();
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
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
	if (!MovementComponent.IsValid()) {
		return;
	}
	if (FMath::IsNearlyEqual(Amount, 0.f)) {
		MovementComponent->RemoveMovementFlag(Flag);
	}
	else {
		MovementComponent->AddMovementFlag(Flag);
	}
}
