// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Restorer.h"
#include "UObject/NoExportTypes.h"
#include "SnapshotBase.generated.h"

/**
 * Base snapshot
 */
UCLASS()
class MARTAHUB_API USnapshotBase : public UObject, public IRestorer
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Snapshot Base")
	int ReferenceCount;

public:
	/** Increase ReferenceCount */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Base")
	void Take();

	/** Decrease ReferenceCount */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Base")
    void Release();

	/** Indicates if restore is available */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Base")
	bool CanRestore();

	/** Indicates if restore is available */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Snapshot Base")
	int GetReferenceCount();
};
