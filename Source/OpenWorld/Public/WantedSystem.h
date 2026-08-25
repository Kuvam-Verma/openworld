#pragma once

#include "CoreMinimal.h"
#include "Engine/GameStateBase.h"
#include "WantedSystem.generated.h"

UENUM(BlueprintType)
enum class EWantedLevel : uint8
{
	None = 0,
	Low = 1,
	Medium = 2,
	High = 3,
	Critical = 4,
	MaxWanted = 5
};

UCLASS()
class OPENWORLD_API AWantedSystem : public AActor
{
	GENERATED_BODY()

public:
	AWantedSystem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Wanted Level Management
	UFUNCTION(BlueprintCallable, Category = "Wanted")
	void AddWantedLevel(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Wanted")
	void RemoveWantedLevel(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Wanted")
	void ResetWantedLevel();

	UFUNCTION(BlueprintCallable, Category = "Wanted")
	EWantedLevel GetWantedLevel() const { return CurrentWantedLevel; }

	UFUNCTION(BlueprintCallable, Category = "Wanted")
	int32 GetWantedPoints() const { return CurrentWantedPoints; }

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Wanted")
	EWantedLevel CurrentWantedLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Wanted")
	int32 CurrentWantedPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wanted")
	int32 PointsPerLevel = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wanted")
	float DecayRate = 5.f; // Points to decay per second

	void UpdateWantedLevel();
	void DecayWantedLevel(float DeltaTime);
};