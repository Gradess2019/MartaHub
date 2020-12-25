// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PhysicsRestorable.generated.h"

class USnapshotBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPhysicsRestorable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents physical object that can be restored
 */
class MARTAHUB_API IPhysicsRestorable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Physics Restorable")
	USnapshotBase* GetPhysicsSnapshot();
};
