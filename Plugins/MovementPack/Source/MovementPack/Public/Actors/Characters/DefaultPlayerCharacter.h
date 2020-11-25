/// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InputControllable.h"

#include "DefaultPlayerCharacter.generated.h"

/**
 * A default Character that is ready to go.
 * Inherit from it and override controls (if necessary)
 */
UCLASS()
class MOVEMENTPACK_API ADefaultPlayerCharacter : public ACharacter, public IInputControllable
{
	GENERATED_BODY()

public:

	// IInputControllable interface
	virtual void AddForward_Implementation(const float AxisValue) override;
	virtual void AddRight_Implementation(const float AxisValue) override;
	virtual void AddUp_Implementation(const float AxisValue) override;
	virtual void AddTurnAround_Implementation(const float AxisValue) override;
	virtual void AddLookUp_Implementation(const float AxisValue) override;
	virtual void Space_Implementation() override;
};
