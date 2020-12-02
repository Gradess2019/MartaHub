// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootstepSoundComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFootstepSound, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API UFootstepSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Sound | Footstep Sound Component",
		meta = (AdvancedDisplay = 1)
	)
	void Play(
		UPARAM(DisplayName = "SurfaceType")EPhysicalSurface InSurfaceType,
		UPARAM(DisplayName = "Location")FVector InLocation = FVector::ZeroVector,
		UPARAM(DisplayName = "Attenuation")class USoundAttenuation* InAttenuation = nullptr
	);

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Footstep Sound")
	USoundAttenuation* DefaultAttenuation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Footstep Sound")
	TMap<TEnumAsByte<EPhysicalSurface>, class USoundBase*> Sounds;

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Sound | Footstep Sound Component"
	)
	void OverrideAttenuation(
		UPARAM(DisplayName = "Sound")USoundBase* InSound,
		UPARAM(DisplayName = "Attenuation")USoundAttenuation* InAttenuation
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Sound | Footstep Sound Component"
	)
	void OverrideLocation(UPARAM(DisplayName = "Location", ref)FVector& InLocation);

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void FillSoundMap();
#endif
	
	void PrintError(const char* FunctionName, int Line, const char* Message);
};
