// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "UObject/Object.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"
#include "BaseCommand.generated.h"

/**
 * Base class for implementing Command pattern
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class COMMANDPACK_API UBaseCommand : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Command Pack | Base Command",
		meta = (WorldContext = "InWorldContextObject", CallableWithoutWorldContext)
	)
	bool InitWorldContext(UObject* InWorldContextObject);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Command Pack | Base Command")
	void Execute();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Base Command")
	UObject* WorldContextObject;
};
