#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OpenWorldCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Walking,
	Sprinting,
	Crouching,
	Climbing,
	Swimming,
	Exhausted
};

UCLASS()
class OPENWORLD_API AOpenWorldCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOpenWorldCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Enhanced Input System
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UEnhancedInputComponent* EnhancedInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UEnhancedPlayerInput* EnhancedPlayerInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CrouchAction;

	// Camera & Movement Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	// Movement State
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	EMovementState CurrentMovementState;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsSprinting;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsCrouching;

	// Input Callbacks
	void OnMoveInput(const FInputActionValue& Value);
	void OnLookInput(const FInputActionValue& Value);
	void StartSprint();
	void StopSprint();
	void ToggleCrouch();

	// Stamina System
	void UpdateStamina(float DeltaTime);

	// Movement Parameters
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchHeight = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StandingHeight = 88.f;

	// Camera Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraDistance = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraHeight = 60.f;

	// Stamina System
	UPROPERTY(BlueprintReadWrite, Category = "Stamina")
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaDrainRate = 15.f; // Points per second while sprinting

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaRecoveryRate = 8.f; // Points per second while not sprinting

	UPROPERTY(BlueprintReadWrite, Category = "Stamina")
	bool bIsExhausted = false;

	// Combat Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MaxHealth = 100.f;

	// Blueprint accessible functions
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateMovementSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	EMovementState GetCurrentMovementState() const { return CurrentMovementState; }

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetStaminaPercent() const { return Stamina / MaxStamina; }

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool HasStamina() const { return Stamina > 0.f; }
};