// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.generated.h"

/**
 * Base class for implementing State pattern
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class MARTAHUB_API UBaseState : public UObject
{
	GENERATED_BODY()

public:
	
	virtual UWorld* GetWorld() const override;
};
