// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents an object that can be selected
 */
class MARTAHUB_API ISelectable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selectable")
	void Select();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selectable")
	void Unselect();
};
