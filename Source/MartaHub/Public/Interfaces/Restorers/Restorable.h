// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Restorable.generated.h"

class ISnapshotManager;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URestorable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents physical object that can be restored
 */
class MARTAHUB_API IRestorable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Restorable")
	TScriptInterface<ISnapshotManager> GetSnapshotManager();
};
