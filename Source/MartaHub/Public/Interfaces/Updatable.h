// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Updatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUpdatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents updatable object
 */
class MARTAHUB_API IUpdatable
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Updatable"
	)
	void Update(const float DeltaTime);
};
