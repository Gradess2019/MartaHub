// Gradess Games. All rights reserved.

#include "Libraries/RadioHelper.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundClass.h"
#include "MediaAssets/Public/MediaSoundComponent.h"

float URadioHelper::GetVolume(UAudioComponent* AudioComponent)
{
	return IsValid(AudioComponent) && IsValid(AudioComponent->SoundClassOverride)
               ? AudioComponent->SoundClassOverride->Properties.Volume
               : -1.f;
}

float URadioHelper::GetMediaVolume(UMediaSoundComponent* MediaSoundComponent)
{
	return IsValid(MediaSoundComponent) && IsValid(MediaSoundComponent->SoundClass)
		       ? MediaSoundComponent->SoundClass->Properties.Volume
		       : -1.f;
}

void URadioHelper::SetVolume(UAudioComponent* AudioComponent, const float Volume)
{
	if (!(IsValid(AudioComponent) && IsValid(AudioComponent->SoundClassOverride))) { return; }
	AudioComponent->SoundClassOverride->Properties.Volume = Volume;
}

void URadioHelper::SetMediaVolume(UMediaSoundComponent* MediaSoundComponent, const float Volume)
{
	if (!(IsValid(MediaSoundComponent) && IsValid(MediaSoundComponent->SoundClass))) { return; }
	MediaSoundComponent->SoundClass->Properties.Volume = Volume;
}
