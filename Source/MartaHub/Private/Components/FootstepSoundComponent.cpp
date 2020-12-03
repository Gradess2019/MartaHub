// Gradess Games. All rights reserved.

#include "Components/FootstepSoundComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsSettings.h"

DEFINE_LOG_CATEGORY(LogFootstepSound);

void UFootstepSoundComponent::Play_Implementation(
	EPhysicalSurface InSurfaceType,
	FVector InLocation,
	USoundAttenuation* InAttenuation
)
{
	if (!Sounds.Contains(InSurfaceType))
	{
		PrintError(__FUNCTION__, __LINE__, "Unknown surface type!");
		return;
	}

	auto SoundPtr = Sounds.Find(InSurfaceType);
	if (!SoundPtr)
	{
		PrintError(__FUNCTION__, __LINE__, "Sound is null!");
		return;
	}

	auto Sound = *SoundPtr;
	OverrideAttenuation(Sound, InAttenuation);
	OverrideLocation(InLocation);
	UGameplayStatics::PlaySoundAtLocation(this, Sound, InLocation);
}

void UFootstepSoundComponent::PlayHit_Implementation(const FHitResult& InHit)
{
	const auto SurfaceType = UGameplayStatics::GetSurfaceType(InHit);
	const auto Location = InHit.ImpactPoint;
	Play(SurfaceType, Location);
}

void UFootstepSoundComponent::PrintError(const char* FunctionName, int Line, const char* Message)
{
	UE_LOG(
		LogFootstepSound,
		Error,
		TEXT("%s => Line: %d: %s"),
		*FString(FunctionName),
		Line,
		*FString(Message)
	);
}

void UFootstepSoundComponent::OverrideAttenuation_Implementation(USoundBase* InSound, USoundAttenuation* InAttenuation)
{
	const auto Attenuation = IsValid(InAttenuation) ? InAttenuation : DefaultAttenuation;
	InSound->AttenuationSettings = Attenuation;
}

void UFootstepSoundComponent::OverrideLocation_Implementation(FVector& InLocation)
{
	InLocation = InLocation.IsZero() ? GetOwner()->GetActorLocation() : InLocation;
}

#if WITH_EDITOR
void UFootstepSoundComponent::FillSoundMap()
{
	const auto Settings = UPhysicsSettings::Get();
	const auto PhysicalSurfaces = &Settings->PhysicalSurfaces;
	const auto Surfaces = PhysicalSurfaces->GetData();
	for (int i = 0; i < PhysicalSurfaces->Num(); i++)
	{
		Sounds.Add(Surfaces[i].Type, nullptr);
	}
}
#endif
