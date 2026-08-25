#include "MobileHUD.h"
#include "MobileCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMobileHUD::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerCharacter = Cast<AMobileCharacter>(GetOwningPlayerPawn());
}

void UMobileHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!PlayerCharacter) return;

	if (HealthBar)
	{
		HealthBar->SetPercent(PlayerCharacter->Health / PlayerCharacter->MaxHealth);
	}

	if (StaminaBar)
	{
		StaminaBar->SetPercent(PlayerCharacter->GetStaminaPercent());
	}

	if (MoneyText)
	{
		MoneyText->SetText(FText::FromString(FString::Printf(TEXT("$%d"), PlayerMoney)));
	}
}