// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SessionHelper.generated.h"

class APlayerController;

/**
 * Session helper
 */
UCLASS()
class MARTAHUB_API USessionHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "Session Helper",
		meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext)
	)
	static bool IsSession(
		UObject* WorldContextObject
	);
};
