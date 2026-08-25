#include "OpenWorldGameMode.h"

AOpenWorldGameMode::AOpenWorldGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOpenWorldGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Game Started - Money: $%d"), PlayerMoney);
}

void AOpenWorldGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOpenWorldGameMode::AddMoney(int32 Amount)
{
	PlayerMoney += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Money: +$%d (Total: $%d)"), Amount, PlayerMoney);
}

void AOpenWorldGameMode::RemoveMoney(int32 Amount)
{
	PlayerMoney -= Amount;
	if (PlayerMoney < 0) PlayerMoney = 0;
	UE_LOG(LogTemp, Warning, TEXT("Money: -$%d (Total: $%d)"), Amount, PlayerMoney);
}

void AOpenWorldGameMode::AddReputation(int32 Amount)
{
	PlayerReputation += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Reputation: +%d (Total: %d)"), Amount, PlayerReputation);
}