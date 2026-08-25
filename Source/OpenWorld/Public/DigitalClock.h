#pragma once

#include "CoreMinimal.h"
#include "Engine/Actor.h"
#include "DigitalClock.generated.h"

UENUM(BlueprintType)
enum class ETimeZone : uint8
{
	UTC = 0,
	EST = 1,      // Eastern Standard Time (UTC-5)
	CST = 2,      // Central Standard Time (UTC-6)
	MST = 3,      // Mountain Standard Time (UTC-7)
	PST = 4,      // Pacific Standard Time (UTC-8)
	GMT = 5,      // Greenwich Mean Time (UTC+0)
	CET = 6,      // Central European Time (UTC+1)
	IST = 7,      // Indian Standard Time (UTC+5:30)
	JST = 8,      // Japan Standard Time (UTC+9)
	AEST = 9,     // Australian Eastern Standard Time (UTC+10)
	NZST = 10     // New Zealand Standard Time (UTC+12)
};

USTRUCT(BlueprintType)
struct FTimeZoneData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETimeZone TimeZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TimeZoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UtcOffset; // Hours offset from UTC

	UPROPERTY(BlueprintReadWrite)
	FString CurrentTime;
};

UCLASS()
class OPENWORLD_API ADigitalClock : public AActor
{
	GENERATED_BODY()

public:
	ADigitalClock();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Time display functions
	UFUNCTION(BlueprintCallable, Category = "Clock")
	FString GetTimeString(ETimeZone TimeZone);

	UFUNCTION(BlueprintCallable, Category = "Clock")
	FString GetTimeStringFormatted(ETimeZone TimeZone, bool bIncludeSeconds = true);

	UFUNCTION(BlueprintCallable, Category = "Clock")
	FTimeZoneData GetTimeZoneData(ETimeZone TimeZone);

	UFUNCTION(BlueprintCallable, Category = "Clock")
	TArray<FTimeZoneData> GetAllTimeZones();

	UFUNCTION(BlueprintCallable, Category = "Clock")
	FString GetCurrentGameTime();

	UFUNCTION(BlueprintCallable, Category = "Clock")
	void SetGameTime(int32 Hours, int32 Minutes, int32 Seconds);

	UFUNCTION(BlueprintCallable, Category = "Clock")
	void ResetToRealTime();

	// Time control
	UFUNCTION(BlueprintCallable, Category = "Clock")
	void AdvanceTime(float Seconds);

	UFUNCTION(BlueprintCallable, Category = "Clock")
	void SetTimeSpeed(float Speed); // 1.0 = real time, 2.0 = 2x speed, etc.

protected:
	// Stored game time (in seconds since midnight)
	UPROPERTY(BlueprintReadWrite, Category = "Clock")
	double GameTime = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	float TimeSpeedMultiplier = 1.0f; // Game time multiplier (1.0 = real time)

	// Helper functions
	FString FormatTime(double TimeInSeconds, bool bIncludeSeconds = true);
	FTimeZoneData CreateTimeZoneData(ETimeZone TimeZone, const FString& Name, float Offset);
	double ConvertToTimeZone(double GameTime, float UtcOffset);

	// Update all time zones
	UPROPERTY(BlueprintReadWrite, Category = "Clock")
	TArray<FTimeZoneData> TimeZones;

	void UpdateTimeZones();
};
