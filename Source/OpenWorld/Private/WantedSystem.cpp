#include "WantedSystem.h"

AWantedSystem::AWantedSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWantedSystem::BeginPlay()
{
	Super::BeginPlay();
	CurrentWantedLevel = EWantedLevel::None;
	CurrentWantedPoints = 0;
}

void AWantedSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DecayWantedLevel(DeltaTime);
	UpdateWantedLevel();
}

void AWantedSystem::AddCrime()
{
	int32 CurrentLevel = static_cast<int32>(CurrentWantedLevel);
	CurrentLevel = FMath::Clamp(CurrentLevel + 1, 0, 5);
	CurrentWantedLevel = static_cast<EWantedLevel>(CurrentLevel);
	UE_LOG(LogTemp, Warning, TEXT("Crime! Wanted Level: %d STARS"), CurrentLevel);
}

void AWantedSystem::LosePolice()
{
	CurrentWantedLevel = EWantedLevel::None;
	CurrentWantedPoints = 0;
	UE_LOG(LogTemp, Warning, TEXT("Escaped Police! 0 STARS"));
}

void AWantedSystem::UpdateWantedLevel()
{
	int32 NewLevel = CurrentWantedPoints / PointsPerLevel;
	NewLevel = FMath::Clamp(NewLevel, 0, 5);
	CurrentWantedLevel = static_cast<EWantedLevel>(NewLevel);
}

void AWantedSystem::DecayWantedLevel(float DeltaTime)
{
	if (CurrentWantedPoints > 0)
	{
		CurrentWantedPoints = FMath::Max(0, CurrentWantedPoints - static_cast<int32>(DecayRate * DeltaTime));
	}
}