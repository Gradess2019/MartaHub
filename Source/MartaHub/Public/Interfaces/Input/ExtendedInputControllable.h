// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExtendedInputControllable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UExtendedInputControllable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents a pawn with extended input
 */
class MARTAHUB_API IExtendedInputControllable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Extended Input Controllable")
	void AuxiliaryInteract();
};
