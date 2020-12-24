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
	
};
