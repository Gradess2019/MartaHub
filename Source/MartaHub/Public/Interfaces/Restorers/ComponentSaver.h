// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComponentSaver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UComponentSaver : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MARTAHUB_API IComponentSaver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Component Saver")
    bool Save(UPARAM(DisplayName = "Component") UActorComponent* InComponent);
};
