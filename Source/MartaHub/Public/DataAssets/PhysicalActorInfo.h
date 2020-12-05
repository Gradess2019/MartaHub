// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PhysicalActorInfo.generated.h"

/**
 * Data asset for physical actors such as cup, table, armchair, etc.
 */
UCLASS()
class MARTAHUB_API UPhysicalActorInfo : public UDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Mass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* Mesh;
};
