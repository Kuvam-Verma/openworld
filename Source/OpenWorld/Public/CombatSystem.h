#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatSystem.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed,
	Pistol,
	Rifle,
	Shotgun,
	Sniper,
	Melee
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoCapacity = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accuracy = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 5000.f;
};

UCLASS()
class OPENWORLD_API ACombatSystem : public AActor
{
	GENERATED_BODY()

public:
	ACombatSystem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Combat Actions
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void FireWeapon();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void MeleeAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EquipWeapon(EWeaponType WeaponType);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyDamage(AActor* TargetActor, float DamageAmount);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FWeaponStats CurrentWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	int32 CurrentAmmo = 30;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	float LastFireTime = 0.f;

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	EWeaponType GetCurrentWeapon() const { return CurrentWeapon.WeaponType; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetCurrentAmmo() const { return CurrentAmmo; }
};