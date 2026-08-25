#include "OpenWorldCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AOpenWorldCharacter::AOpenWorldCharacter()
{
	// Don't rotate character with camera
	bAutoManageActiveCamera = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, CameraHeight);
	CameraBoom->bUsePawnControlRotation = true;

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AOpenWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	Stamina = MaxStamina;
	Health = MaxHealth;
}

void AOpenWorldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);
	UpdateMovementSpeed();
}

void AOpenWorldCharacter::UpdateStamina(float DeltaTime)
{
	if (bIsSprinting && Stamina > 0.f)
	{
		// Drain stamina while sprinting
		Stamina -= DeltaTime * StaminaDrainRate;

		if (Stamina <= 0.f)
		{
			Stamina = 0.f;
			bIsSprinting = false;
			bIsExhausted = true;
			CurrentMovementState = EMovementState::Exhausted;
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; // Force walk
		}
	}
	else
	{
		// Recover stamina when not sprinting
		Stamina = FMath::Min(MaxStamina, Stamina + DeltaTime * StaminaRecoveryRate);

		// Clear exhausted state when stamina fully recovered
		if (Stamina >= MaxStamina)
		{
			bIsExhausted = false;
		}
	}
}

void AOpenWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::OnMoveInput);
		}

		// Looking
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::OnLookInput);
		}

		// Sprinting
		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AOpenWorldCharacter::StartSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AOpenWorldCharacter::StopSprint);
		}

		// Crouching
		if (CrouchAction)
		{
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::ToggleCrouch);
		}
	}
}

void AOpenWorldCharacter::OnMoveInput(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Forward movement
	if (MovementVector.Y != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	}

	// Right movement
	if (MovementVector.X != 0.f)
	{
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AOpenWorldCharacter::OnLookInput(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Add yaw and pitch input to controller
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AOpenWorldCharacter::StartSprint()
{
	// Can only sprint if we have stamina and are not exhausted
	if (!bIsExhausted && Stamina > 0.f && !bIsCrouching)
	{
		bIsSprinting = true;
		CurrentMovementState = EMovementState::Sprinting;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AOpenWorldCharacter::StopSprint()
{
	bIsSprinting = false;
	if (!bIsCrouching)
	{
		CurrentMovementState = EMovementState::Walking;
	}
}

void AOpenWorldCharacter::ToggleCrouch()
{
	if (bIsCrouching)
	{
		UnCrouch();
		bIsCrouching = false;
		CurrentMovementState = EMovementState::Walking;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		Crouch();
		bIsCrouching = true;
		bIsSprinting = false;
		CurrentMovementState = EMovementState::Crouching;
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
	}
}

void AOpenWorldCharacter::UpdateMovementSpeed()
{
	if (bIsSprinting && !bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else if (bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AOpenWorldCharacter::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.f)
	{
		Health = 0.f;
		GetCharacterMovement()->DisableMovement();
		UE_LOG(LogTemp, Warning, TEXT("Character died!"));
	}
}