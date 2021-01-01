// Gradess Games. All rights reserved.

#include "Actors/Radio.h"
#include "MediaSoundComponent.h"
#include "RadioStationPlaylist.h"
#include "MediaPlayer.h"
#include "Interfaces/RadioReplicator.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/RadioHelper.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"

ARadio::ARadio()
{
	MediaSoundComponent = CreateDefaultSubobject<UMediaSoundComponent>(FName("MediaSound"));
	MediaSoundComponent->SetupAttachment(RootComponent);

	const auto MediaPlayerPath = TEXT("MediaPlayer'/SimpleRadio/Media/MP_Radio.MP_Radio'");
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> MediaPlayerAsset(MediaPlayerPath);
	MediaPlayer = MediaPlayerAsset.Object;
#if WITH_EDITOR
	MediaSoundComponent->SetDefaultMediaPlayer(MediaPlayer);
#endif

	MediaSoundComponent->bAllowSpatialization = true;

	const auto AttenuationPath = TEXT("SoundAttenuation'/SimpleRadio/Sound/ATT_Radio.ATT_Radio'");
	static ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenuationAsset(AttenuationPath);
	const auto Attenuation = AttenuationAsset.Object;
	MediaSoundComponent->AttenuationSettings = Attenuation;

	MinVolume = 0.f;
	MaxVolume = 1.f;

	bAutoPlay = true;

	bStaticMeshReplicateMovement = true;
	bReplicates = true;
}

void ARadio::BeginPlay()
{
	Super::BeginPlay();

#if !WITH_EDITOR
	MediaSoundComponent->SetMediaPlayer(MediaPlayer);
	MediaSoundComponent->UpdatePlayer();
#endif

	const auto bServer = HasAuthority();
	if (!bServer) { return; }

	BindUnlockFunction();
	SetupStreams();
	SetupVolume();
}

void ARadio::BindUnlockFunction_Implementation()
{
	FScriptDelegate UnlockDelegate;
	UnlockDelegate.BindUFunction(this, "Unlock");

	auto CurrentMediaPlayer = GetMedia();
	CurrentMediaPlayer->OnMediaOpened.Add(UnlockDelegate);
	CurrentMediaPlayer->OnMediaOpenFailed.Add(UnlockDelegate);
}

void ARadio::SetupStreams_Implementation()
{
	Streams = URadioStationPlaylist::GetStreams();

	if (!bAutoPlay) { return; }

	PlayById(0);
}

void ARadio::SetupVolume_Implementation()
{
	const auto InitialVolume = URadioHelper::GetMediaVolume(MediaSoundComponent);
	SetVolume(InitialVolume);
}

void ARadio::SetVolume_Implementation(const float NewVolume)
{
	Volume = NewVolume;
}

void ARadio::Open_Implementation(const FString& URL)
{
	auto CurrentMediaPlayer = GetMedia();
	CurrentMediaPlayer->Close();
	CurrentMediaPlayer->OpenUrl(URL);
}

UMediaPlayer* ARadio::GetMedia_Implementation()
{
	return MediaSoundComponent->GetMediaPlayer();
}

void ARadio::Play_Implementation(const FString& URL)
{
	const auto bAuthority = HasAuthority();
	if (bAuthority)
	{
		if (bLock || CurrentStream.Equals(URL, ESearchCase::IgnoreCase)) { return; }

		CurrentStream = URL;

#if !UE_SERVER
		OnRep_CurrentStream();
#endif
		Lock();

#if UE_SERVER
		UE_LOG(LogTemp, Warning, TEXT("Dedicated server"));
		FTimerHandle UnlockTimer;
		GetWorldTimerManager().SetTimer(
			UnlockTimer,
			this,
			&ARadio::Unlock,
			2.f
		);
#endif
	}
	else
	{
		const auto RadioReplicator = GetRadioReplicator();
		if (!IsValid(RadioReplicator)) { return; }

		IRadioReplicator::Execute_Play(RadioReplicator, this, URL);
	}
}

void ARadio::Lock_Implementation()
{
	bLock = true;
}

void ARadio::OnRep_CurrentStream_Implementation()
{
	Open(CurrentStream);
}

void ARadio::Unlock_Implementation()
{
	bLock = false;
}

UObject* ARadio::GetRadioReplicator_Implementation()
{
	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	const auto bImplements = PlayerController->Implements<URadioReplicator>();
	return bImplements ? PlayerController : nullptr;
}

void ARadio::PlayNext_Implementation()
{
	const auto CurrentStreamId = Streams.Find(CurrentStream);
	const auto NextStreamId = (CurrentStreamId + 1) % Streams.Num();

	PlayById(NextStreamId);
}

void ARadio::PlayById_Implementation(const int Id)
{
	const auto bValidIndex = Streams.IsValidIndex(Id);
	if (!bValidIndex) { return; }

	const auto NewStream = Streams[Id];
	Play(NewStream);
}

void ARadio::PlayPrevious_Implementation()
{
	const auto CurrentStreamId = Streams.Find(CurrentStream);
	const auto PreviousStreamId = CurrentStreamId - 1 < 0 ? Streams.Num() - 1 : CurrentStreamId - 1;

	PlayById(PreviousStreamId);
}

void ARadio::AdjustVolume_Implementation(const float Delta)
{
	const auto bServer = HasAuthority();
	if (bServer)
	{
		const float NewVolume = CalculateNewVolume(Delta);
		SetVolume(NewVolume);
		OnRep_Volume();
	}
	else
	{
		const auto RadioReplicator = GetRadioReplicator();
		if (!IsValid(RadioReplicator)) { return; }

		IRadioReplicator::Execute_AdjustVolume(RadioReplicator, this, Delta);
	}
}

float ARadio::CalculateNewVolume_Implementation(const float Delta)
{
	const auto CurrentVolume = URadioHelper::GetMediaVolume(MediaSoundComponent);
	const auto NewVolume = FMath::Clamp(CurrentVolume + Delta, MinVolume, MaxVolume);
	return NewVolume;
}

void ARadio::OnRep_Volume_Implementation()
{
	SetVolumeInternal(Volume);
}

void ARadio::SetVolumeInternal_Implementation(const float NewVolume)
{
	URadioHelper::SetMediaVolume(MediaSoundComponent, NewVolume);
}

void ARadio::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARadio, CurrentStream);
	DOREPLIFETIME(ARadio, Volume);
	DOREPLIFETIME_CONDITION(ARadio, Streams, COND_InitialOnly);
}
