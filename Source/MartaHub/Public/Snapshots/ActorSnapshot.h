// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnapshotBase.h"
#include "Interfaces/Restorers/ActorSaver.h"
#include "ActorSnapshot.generated.h"

/**
 * Base class for snapshotting actor state
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class MARTAHUB_API UActorSnapshot : public USnapshotBase, public IActorSaver
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Actor Snapshot")
	AActor* Actor;

public:

	virtual bool Save_Implementation(AActor* InActor) override;
};
