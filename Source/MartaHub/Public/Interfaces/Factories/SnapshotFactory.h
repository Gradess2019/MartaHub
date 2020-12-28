// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Snapshots/SnapshotBase.h"
#include "SnapshotFactory.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USnapshotFactory : public UInterface
{
	GENERATED_BODY()
};

/**
 * Snapshot Factory interface
 */
class MARTAHUB_API ISnapshotFactory
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Factory")
	USnapshotBase* CreateSnapshot(TSubclassOf<USnapshotBase> Class);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Factory")
    USnapshotBase* CreateComponentPhysicsSnapshot();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Factory")
	USnapshotBase* CreateActorPhysicsSnapshot();
};
