#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MobileHUD.generated.h"

class AMobileCharacter;

UCLASS()
class OPENWORLD_API UMobileHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WantedStarsText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyText;

protected:
	AMobileCharacter* PlayerCharacter;
	int32 PlayerMoney = 1000;
};