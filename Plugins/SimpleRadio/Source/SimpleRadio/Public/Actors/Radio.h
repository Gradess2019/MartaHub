// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Radio.generated.h"

class UMediaSoundComponent;
class UMediaPlayer;

UCLASS(BlueprintType, Blueprintable)
class SIMPLERADIO_API ARadio : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ARadio();

protected:
	/** Media sound component*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Radio")
	UMediaSoundComponent* MediaSoundComponent;

	/** Media player of Media Sound Component*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Radio")
	UMediaPlayer* MediaPlayer;

	/** Should play media on begin play */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Radio")
	bool bAutoPlay;

	/** Indicates whether radio is connection to stream. Prevents crash */
	UPROPERTY(BlueprintReadWrite, Category = "Radio | Stream")
	bool bLock;

	/** Current connected stream */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_CurrentStream, Category = "Radio | Stream")
	FString CurrentStream;

	/** Available streams to connect */
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Radio | Stream")
	TArray<FString> Streams;

	/** Current volume of radio */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_Volume, Category = "Radio | Volume")
	float Volume;

	/** Min volume of radio */
	UPROPERTY(BlueprintReadWrite, Category = "Radio | Volume")
	float MinVolume;

	/** Max volume of radio */
	UPROPERTY(BlueprintReadWrite, Category = "Radio | Volume")
	float MaxVolume;

	virtual void BeginPlay() override;

	/** Binds Unlock() to OnMediaOpened and OnMediaOpenFailed delegates */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Radio | Stream")
	void BindUnlockFunction();

	/** Loads streams from configuration file */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Radio | Stream")
	void SetupStreams();

	/** Sets initial volume */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Radio | Volume")
	void SetupVolume();

public:
	/** Sets volume */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Radio | Volume")
	void SetVolume(const float NewVolume);

protected:
	/** Opens stream URL */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Stream")
	void Open(const FString& URL);

public:
	/** Returns current Media Player */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio")
	UMediaPlayer* GetMedia();

	/** Play new stream */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Stream")
	void Play(const FString& URL);

protected:
	/** Locks Play() while radio is connecting to new stream */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Radio | Stream")
	void Lock();

	UFUNCTION(BlueprintNativeEvent, Category = "Radio | Stream")
	void OnRep_CurrentStream();

	/** Unlocks Play() method */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Radio | Stream")
	void Unlock();

public:
	/** Returns object that is in charge of radio replication (used for calling RPCs) */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio")
	UObject* GetRadioReplicator();

	/** Plays next stream */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Stream")
	void PlayNext();

	/** Plays stream by index (in Streams array) */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Stream")
	void PlayById(const int Id);

	/** Plays previous stream */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Stream")
	void PlayPrevious();

	/** Decreases or increases volume of radio */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Volume")
	void AdjustVolume(const float Delta = 0.05f);

protected:
	/** Calculates new volume */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Volume")
	float CalculateNewVolume(const float Delta);

	UFUNCTION(BlueprintNativeEvent, Category = "Radio | Volume")
	void OnRep_Volume();

	/** Set volume of media sound component. Doesn't replicate Volume variable, use SetVolume() instead.  */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio | Volume")
	void SetVolumeInternal(const float NewVolume);

	virtual void GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
