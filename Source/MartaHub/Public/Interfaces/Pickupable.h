// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickupable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickupable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents an object that can be pickuped by someone
 */
class MARTAHUB_API IPickupable
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable"
	)
	void SetPickupLocation(
		const FVector& OwnerLocation,
		const FVector& OwnerDirection
	);

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable"
	)
	void PrepareForPickup();

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable"
	)
	void ClearPickup();

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable"
	)
	void Throw(
		float Force
	);
};
