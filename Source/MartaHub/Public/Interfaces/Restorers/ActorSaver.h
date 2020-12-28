// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorSaver.generated.h"

UINTERFACE(MinimalAPI)
class UActorSaver : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents actor saver object
 */
class MARTAHUB_API IActorSaver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Saver")
    bool Save(UPARAM(DisplayName = "Actor") AActor* InActor);
};
