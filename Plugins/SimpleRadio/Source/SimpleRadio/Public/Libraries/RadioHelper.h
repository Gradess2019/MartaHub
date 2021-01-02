// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RadioHelper.generated.h"

class UAudioComponent;
class UMediaSoundComponent;

/**
 * Radio Helper library
 */
UCLASS()
class SIMPLERADIO_API URadioHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Radio Helper")
	static float GetVolume(UAudioComponent* AudioComponent);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Radio Helper")
    static float GetMediaVolume(UMediaSoundComponent* MediaSoundComponent);

	UFUNCTION(BlueprintCallable, Category = "Radio Helper")
	static void SetVolume(UAudioComponent* AudioComponent, const float Volume = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Radio Helper")
    static void SetMediaVolume(UMediaSoundComponent* MediaSoundComponent, const float Volume = 0.f);
};
