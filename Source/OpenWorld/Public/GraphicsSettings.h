#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

class OPENWORLD_API FGraphicsSettings
{
public:
	/**
	 * Enable high-end graphics settings for cinematic open-world visuals
	 * Includes Nanite, Lumen, Virtual Shadow Maps, and advanced post-processing
	 */
	static void EnableHighGraphics(UWorld* World);

	/**
	 * Enable medium graphics settings for balanced performance
	 */
	static void EnableMediumGraphics(UWorld* World);

	/**
	 * Enable low graphics settings for performance on weaker hardware
	 */
	static void EnableLowGraphics(UWorld* World);

	/**
	 * Toggle a specific graphics setting
	 */
	static void SetGraphicsSetting(UWorld* World, const TCHAR* Command, const TCHAR* Value);
};