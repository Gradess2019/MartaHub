// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputControllable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputControllable : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface that represents default controllable object
 */
class MOVEMENTPACK_API IInputControllable
{
	GENERATED_BODY()

public:
	/** Moves actor forward */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void AddForward(const float AxisValue);

	/** Moves actor rightward */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void AddRight(const float AxisValue);

	/** Moves actor upward */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void AddUp(const float AxisValue);

	/** Rotates actor around itself (Yaw) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void AddTurnAround(const float AxisValue);

	/** Rotates actor up and down (Pitch) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void AddLookUp(const float AxisValue);

	/** Allows actor to zoom in or out, speed up or down, etc. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void AddScroll(const float AxisValue);

	/** Allows actor to hit, fire, etc. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void Fire();

	/** Allows actor to interact with other ones */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void Interact();

	/** Allows actor to use jump, brakes, etc. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Pack")
	void Space();
};
