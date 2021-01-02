// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SnapshotManager.generated.h"

class USnapshotBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USnapshotManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents SnapshotManager object
 */
class MARTAHUB_API ISnapshotManager
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Manager")
	USnapshotBase* TakeSnapshot(TSubclassOf<USnapshotBase> Class);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Manager")
    void ReleaseSnapshot(USnapshotBase* Snapshot);
};
