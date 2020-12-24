// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RestorerHelper.generated.h"

/**
 * Restorer Helper library
 */
UCLASS()
class MARTAHUB_API URestorerHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Restorer Helper")
	static void DisablePhysicsAndCollision(AActor* Actor, const bool bIncludeChildren = true);
};
