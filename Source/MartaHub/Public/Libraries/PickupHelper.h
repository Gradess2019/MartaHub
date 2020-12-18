// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PickupHelper.generated.h"

/**
 * Pickup helper
 */
UCLASS()
class MARTAHUB_API UPickupHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "Pickup Helper",
		meta = (AdvancedDisplay = 4)
	)
	static FVector CalculatePickupLocation(
		AActor* Target,
		const FVector OwnerLocation = FVector::ZeroVector,
		const FVector OwnerDirection = FVector::ZeroVector,
		const FVector Offset = FVector::ZeroVector,
		const float Bound = 0.f,
		const float Alpha = 1.f
	);
	
	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "Pickup Helper",
		meta = (AdvancedDisplay = 2)
	)
	static FRotator CalculatePickupRotation(
		AActor* Target,
		const FVector OwnerDirection = FVector::ZeroVector,
		const float Alpha = 1.f
	);
};
