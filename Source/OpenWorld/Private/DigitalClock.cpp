#include "DigitalClock.h"
#include "Kismet/GameplayStatics.h"

ADigitalClock::ADigitalClock()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f; // Update every 0.1 seconds

	// Initialize game time to current real time
	GameTime = 0.0;
}

void ADigitalClock::BeginPlay()
{
	Super::BeginPlay();

	// Initialize time zones
	TimeZones.Empty();
	TimeZones.Add(CreateTimeZoneData(ETimeZone::UTC, TEXT("UTC"), 0.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::EST, TEXT("EST"), -5.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::CST, TEXT("CST"), -6.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::MST, TEXT("MST"), -7.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::PST, TEXT("PST"), -8.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::GMT, TEXT("GMT"), 0.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::CET, TEXT("CET"), 1.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::IST, TEXT("IST"), 5.5f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::JST, TEXT("JST"), 9.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::AEST, TEXT("AEST"), 10.0f));
	TimeZones.Add(CreateTimeZoneData(ETimeZone::NZST, TEXT("NZST"), 12.0f));

	ResetToRealTime();
	UE_LOG(LogTemp, Warning, TEXT("Digital Clock Initialized"));
}

void ADigitalClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Advance game time
	GameTime += DeltaTime * TimeSpeedMultiplier;

	// Keep time within a 24-hour cycle (86400 seconds = 24 hours)
	if (GameTime >= 86400.0)
	{
		GameTime -= 86400.0;
	}

	// Update all time zones
	UpdateTimeZones();
}

FString ADigitalClock::GetTimeString(ETimeZone TimeZone)
{
	double ConvertedTime = ConvertToTimeZone(GameTime, GetTimeZoneData(TimeZone).UtcOffset);
	return FormatTime(ConvertedTime, true);
}

FString ADigitalClock::GetTimeStringFormatted(ETimeZone TimeZone, bool bIncludeSeconds)
{
	double ConvertedTime = ConvertToTimeZone(GameTime, GetTimeZoneData(TimeZone).UtcOffset);
	return FormatTime(ConvertedTime, bIncludeSeconds);
}

FTimeZoneData ADigitalClock::GetTimeZoneData(ETimeZone TimeZone)
{
	for (const FTimeZoneData& TZ : TimeZones)
	{
		if (TZ.TimeZone == TimeZone)
		{
			return TZ;
		}
	}

	// Return UTC as default
	return TimeZones[0];
}

TArray<FTimeZoneData> ADigitalClock::GetAllTimeZones()
{
	return TimeZones;
}

FString ADigitalClock::GetCurrentGameTime()
{
	return FormatTime(GameTime, true);
}

void ADigitalClock::SetGameTime(int32 Hours, int32 Minutes, int32 Seconds)
{
	GameTime = (Hours * 3600.0) + (Minutes * 60.0) + Seconds;
	GameTime = FMath::Clamp(GameTime, 0.0, 86399.0);
	UE_LOG(LogTemp, Warning, TEXT("Game Time Set to: %02d:%02d:%02d"), Hours, Minutes, Seconds);
}

void ADigitalClock::ResetToRealTime()
{
	// Get current system time
	FDateTime Now = FDateTime::Now();
	GameTime = (Now.GetHour() * 3600.0) + (Now.GetMinute() * 60.0) + Now.GetSecond();
	UE_LOG(LogTemp, Warning, TEXT("Clock Reset to Real Time"));
}

void ADigitalClock::AdvanceTime(float Seconds)
{
	GameTime += Seconds;
	if (GameTime >= 86400.0)
	{
		GameTime -= 86400.0;
	}
}

void ADigitalClock::SetTimeSpeed(float Speed)
{
	TimeSpeedMultiplier = FMath::Max(Speed, 0.1f);
	UE_LOG(LogTemp, Warning, TEXT("Time Speed Set to: %.2fx"), TimeSpeedMultiplier);
}

FString ADigitalClock::FormatTime(double TimeInSeconds, bool bIncludeSeconds)
{
	// Ensure time is within 24 hour range
	double AdjustedTime = FMath::Fmod(TimeInSeconds, 86400.0);
	if (AdjustedTime < 0)
	{\n		AdjustedTime += 86400.0;\n	}

	int32 Hours = static_cast<int32>(AdjustedTime) / 3600;
	int32 Minutes = (static_cast<int32>(AdjustedTime) % 3600) / 60;
	int32 Seconds = static_cast<int32>(AdjustedTime) % 60;

	if (bIncludeSeconds)
	{
		return FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Minutes, Seconds);
	}
	else
	{
		return FString::Printf(TEXT("%02d:%02d"), Hours, Minutes);
	}
}

FTimeZoneData ADigitalClock::CreateTimeZoneData(ETimeZone TimeZone, const FString& Name, float Offset)
{
	FTimeZoneData Data;
	Data.TimeZone = TimeZone;
	Data.TimeZoneName = Name;
	Data.UtcOffset = Offset;
	Data.CurrentTime = TEXT("00:00:00");
	return Data;
}

double ADigitalClock::ConvertToTimeZone(double GameTime, float UtcOffset)
{
	// Convert UTC time to specific time zone
	double OffsetSeconds = UtcOffset * 3600.0;
	double ConvertedTime = GameTime + OffsetSeconds;

	// Keep within 24-hour cycle
	while (ConvertedTime >= 86400.0)
	{
		ConvertedTime -= 86400.0;
	}
	while (ConvertedTime < 0.0)
	{
		ConvertedTime += 86400.0;
	}

	return ConvertedTime;
}

void ADigitalClock::UpdateTimeZones()
{
	for (FTimeZoneData& TZ : TimeZones)
	{
		double ConvertedTime = ConvertToTimeZone(GameTime, TZ.UtcOffset);
		TZ.CurrentTime = FormatTime(ConvertedTime, true);
	}
}
