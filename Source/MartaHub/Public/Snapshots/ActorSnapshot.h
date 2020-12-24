// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnapshotBase.h"
#include "ActorSnapshot.generated.h"

/**
 * Base class for snapshotting actor state
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class MARTAHUB_API UActorSnapshot : public USnapshotBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Actor Snapshot")
	AActor* Actor;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Snapshot")
	bool Save(UPARAM(DisplayName = "Actor") AActor* InActor);
};
