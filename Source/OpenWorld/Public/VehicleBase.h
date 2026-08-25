#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "VehicleBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EVehicleType : uint8
{
	Car,
	Bike,
	Truck,
	Helicopter
};

UCLASS()
class OPENWORLD_API AVehicleBase : public APawn
{
	GENERATED_BODY()

public:
	AVehicleBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	UStaticMeshComponent* VehicleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	// Vehicle Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	EVehicleType VehicleType = EVehicleType::Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	float MaxSpeed = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	float Acceleration = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	float BrakeForce = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	float TurnSpeed = 100.f;

	UPROPERTY(BlueprintReadWrite, Category = "Vehicle")
	float CurrentSpeed = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Vehicle")
	bool bIsEngineRunning = false;

	// Input callbacks
	void OnThrottleInput(const FInputActionValue& Value);
	void OnSteerInput(const FInputActionValue& Value);
	void OnBrakeInput(const FInputActionValue& Value);
	void ToggleEngine();

	// Vehicle control
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void StartEngine();

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void StopEngine();

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void Accelerate(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void Brake(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	void Steer(float Amount);

protected:
	float ThrottleInput = 0.f;
	float SteerInput = 0.f;
	float BrakeInput = 0.f;
};