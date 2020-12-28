// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Restorer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URestorer : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents object that restores itself and/or other object
 */
class MARTAHUB_API IRestorer
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Restorer"
	)
	void Restore();
};
