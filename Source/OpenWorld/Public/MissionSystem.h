#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MissionSystem.generated.h"

UENUM(BlueprintType)
enum class EMissionStatus : uint8
{
	NotStarted,
	Active,
	Completed,
	Failed,
	Abandoned
};

USTRUCT(BlueprintType)
struct FMissionObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCompleted = false;
};

UCLASS(BlueprintType)
class OPENWORLD_API UMissionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MissionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MissionDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMissionObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RewardMoney = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RewardReputation = 10;
};

UCLASS()
class OPENWORLD_API AMissionSystem : public AActor
{
	GENERATED_BODY()

public:
	AMissionSystem();

	virtual void BeginPlay() override;

	// Mission Management
	UFUNCTION(BlueprintCallable, Category = "Mission")
	void StartMission(UMissionData* Mission);

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void CompleteMission();

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void FailMission();

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void AbandonMission();

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void CompleteObjective(int32 ObjectiveIndex);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Mission")
	UMissionData* CurrentMission;

	UPROPERTY(BlueprintReadWrite, Category = "Mission")
	EMissionStatus CurrentMissionStatus;

	UPROPERTY(BlueprintReadWrite, Category = "Mission")
	TArray<UMissionData*> CompletedMissions;

public:
	UFUNCTION(BlueprintCallable, Category = "Mission")
	EMissionStatus GetMissionStatus() const { return CurrentMissionStatus; }

	UFUNCTION(BlueprintCallable, Category = "Mission")
	UMissionData* GetCurrentMission() const { return CurrentMission; }
};