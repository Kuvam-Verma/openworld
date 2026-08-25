#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OpenWorldGameMode.generated.h"

UCLASS()
class OPENWORLD_API AOpenWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOpenWorldGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 PlayerMoney = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 PlayerReputation = 0;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddMoney(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void RemoveMoney(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddReputation(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetPlayerMoney() const { return PlayerMoney; }

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetPlayerReputation() const { return PlayerReputation; }
};
