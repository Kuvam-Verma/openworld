#include "GraphicsSettings.h"

void FGraphicsSettings::EnableHighGraphics(UWorld* World)
{
	if (!World) return;

	// Nanite virtualized geometry
	GEngine->Exec(World, TEXT("r.Nanite 1"));

	// Lumen global illumination and reflections
	GEngine->Exec(World, TEXT("r.Lumen.Reflections.Allow 1"));
	GEngine->Exec(World, TEXT("r.Lumen.GlobalIllumination 1"));

	// Virtual shadow maps for high-quality shadows
	GEngine->Exec(World, TEXT("r.Shadow.Virtual.Enable 1"));

	// Temporal upsampling for better quality
	GEngine->Exec(World, TEXT("r.TemporalAA.Upsampling 1"));

	// Native resolution
	GEngine->Exec(World, TEXT("r.ScreenPercentage 100"));

	// High quality post-processing
	GEngine->Exec(World, TEXT("r.MotionBlurQuality 4"));
	GEngine->Exec(World, TEXT("r.BloomQuality 5"));

	UE_LOG(LogTemp, Warning, TEXT("High Graphics Settings Enabled"));
}

void FGraphicsSettings::EnableMediumGraphics(UWorld* World)
{
	if (!World) return;

	// Nanite disabled
	GEngine->Exec(World, TEXT("r.Nanite 0"));

	// Lumen disabled, use traditional baked lighting
	GEngine->Exec(World, TEXT("r.Lumen.Reflections.Allow 0"));
	GEngine->Exec(World, TEXT("r.Lumen.GlobalIllumination 0"));

	// Standard shadow maps
	GEngine->Exec(World, TEXT("r.Shadow.Virtual.Enable 0"));

	// TAA with slight downsampling
	GEngine->Exec(World, TEXT("r.TemporalAA.Upsampling 0"));
	GEngine->Exec(World, TEXT("r.ScreenPercentage 85"));

	// Medium quality post-processing
	GEngine->Exec(World, TEXT("r.MotionBlurQuality 2"));
	GEngine->Exec(World, TEXT("r.BloomQuality 3"));

	UE_LOG(LogTemp, Warning, TEXT("Medium Graphics Settings Enabled"));
}

void FGraphicsSettings::EnableLowGraphics(UWorld* World)
{
	if (!World) return;

	// Disable advanced rendering features
	GEngine->Exec(World, TEXT("r.Nanite 0"));
	GEngine->Exec(World, TEXT("r.Lumen.Reflections.Allow 0"));
	GEngine->Exec(World, TEXT("r.Lumen.GlobalIllumination 0"));
	GEngine->Exec(World, TEXT("r.Shadow.Virtual.Enable 0"));

	// Aggressive downsampling
	GEngine->Exec(World, TEXT("r.TemporalAA.Upsampling 0"));
	GEngine->Exec(World, TEXT("r.ScreenPercentage 70"));

	// Minimal post-processing
	GEngine->Exec(World, TEXT("r.MotionBlurQuality 0"));
	GEngine->Exec(World, TEXT("r.BloomQuality 1"));

	UE_LOG(LogTemp, Warning, TEXT("Low Graphics Settings Enabled"));
}

void FGraphicsSettings::SetGraphicsSetting(UWorld* World, const TCHAR* Command, const TCHAR* Value)
{
	if (!World || !Command || !Value) return;

	FString FullCommand = FString::Printf(TEXT("%s %s"), Command, Value);
	GEngine->Exec(World, *FullCommand);

	UE_LOG(LogTemp, Warning, TEXT("Graphics Setting Applied: %s"), *FullCommand);
}