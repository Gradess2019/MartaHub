// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RadioReplicator.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URadioReplicator : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents a class that is in charge of Radio replication. E.g. it could be implemented by APlayerController
 */
class SIMPLERADIO_API IRadioReplicator
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio Replicator")
	void AdjustVolume(ARadio* Radio, const float Delta);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio Replicator")
    void Play(ARadio* Radio, const FString& URL);
};
