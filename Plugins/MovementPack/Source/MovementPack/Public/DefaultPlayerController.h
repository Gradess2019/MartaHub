// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

/**
 * A PlayerController that is ready to go.
 * Inherit from it and change default AxisNames and ActionNames (if necessary)
 * Otherwise put DefaultInput.ini inside Config folder of your project
 */
UCLASS(Blueprintable, BlueprintType)
class MOVEMENTPACK_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	ADefaultPlayerController(const FObjectInitializer& ObjectInitializer);

protected:

	// **************************************
	// Input
	// Axis mapping names
	/** Axis mapping name for forward movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Axis Names")
	FName ForwardAxisName;

	/** Axis mapping name for right movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Axis Names")
	FName RightAxisName;

	/** Axis mapping name for up movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Axis Names")
	FName UpAxisName;

	/** Axis mapping name for yaw rotation (e.g. using Mouse X) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Axis Names")
	FName TurnAroundAxisName;

	/** Axis mapping name for pitch rotation (e.g. using Mouse Y) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Axis Names")
	FName LookUpAxisName;

	/** Axis mapping name for scroll (e.g. using Mouse Wheel Axis) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Axis Names")
	FName ScrollAxisName;

	// Action mapping names
	/** Action mapping name for firing (e.g. using Left Mouse Button) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Action Names")
	FName FireActionName;

	/** Action mapping name for interaction (e.g. using Right Mouse Button or 'E') */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Action Names")
	FName InteractActionName;

	/** Action mapping name for jumping (e.g. using Space Bar) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Action Names")
	FName SpaceActionName;

	// Event handlers
	// Axis mappings
	UFUNCTION()
	void MoveForward(const float AxisValue);

	UFUNCTION()
	void MoveRight(const float AxisValue);

	UFUNCTION()
	void MoveUp(const float AxisValue);

	UFUNCTION()
	void TurnAround(const float AxisValue);

	UFUNCTION()
	void LookUp(const float AxisValue);

	UFUNCTION()
	void Scroll(const float AxisValue);

	// Action mappings
	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Space();

	// Setup
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	// **************************************

	UFUNCTION(BlueprintCallable, Category = "Movement Pack | Controller")
	bool IsValidPawn() const;
};
