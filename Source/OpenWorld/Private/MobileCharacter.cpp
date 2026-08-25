#include "MobileCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMobileCharacter::AMobileCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 300.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Mobile optimized camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 40.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMobileCharacter::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;
	Health = MaxHealth;

	UE_LOG(LogTemp, Warning, TEXT("Mobile Character Ready"));
}

void AMobileCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);

	// Handle movement based on joystick input
	if (JoystickInput.Length() > 0.1f)
	{
		FVector Direction = FVector(JoystickInput.Y, JoystickInput.X, 0.f).GetSafeNormal();
		AddMovementInput(GetActorForwardVector(), JoystickInput.Y);
		AddMovementInput(GetActorRightVector(), JoystickInput.X);

		if (bIsRunning && Stamina > 0)
		{
			CurrentState = EMobileMovementState::Running;
			GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		}
		else
		{
			CurrentState = EMobileMovementState::Walking;
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		}
	}
	else
	{
		CurrentState = EMobileMovementState::Idle;
	}
}

void AMobileCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMobileCharacter::OnMoveInput);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMobileCharacter::OnLookInput);
		}
	}
}

void AMobileCharacter::OnMoveInput(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();
	JoystickInput = MovementVector;
}

void AMobileCharacter::OnLookInput(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	LookInput = LookAxisVector;

	AddControllerYawInput(LookAxisVector.X * 0.5f);
	AddControllerPitchInput(LookAxisVector.Y * 0.5f);
}

void AMobileCharacter::OnTouchStarted(const FVector& Location)
{
	bIsRunning = true;
}

void AMobileCharacter::OnTouchMoved(const FVector& Location)
{
	// Mobile camera control
}

void AMobileCharacter::OnTouchEnded()
{
	bIsRunning = false;
	JoystickInput = FVector2D::ZeroVector;
}

void AMobileCharacter::UpdateStamina(float DeltaTime)
{
	if (bIsRunning && Stamina > 0.f)
	{
		Stamina -= DeltaTime * StaminaDrainRate;
		if (Stamina <= 0.f)
		{
			Stamina = 0.f;
			bIsRunning = false;
		}
	}
	else
	{
		Stamina = FMath::Min(MaxStamina, Stamina + DeltaTime * StaminaRecoveryRate);
	}
}

void AMobileCharacter::Attack()
{
	if (Health <= 0.f) return;

	UE_LOG(LogTemp, Warning, TEXT("Attack! Damage: %.0f"), AttackDamage);
}

void AMobileCharacter::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.f)
	{
		Health = 0.f;
		GetCharacterMovement()->DisableMovement();
		UE_LOG(LogTemp, Warning, TEXT("Character Defeated!"));
	}
}
