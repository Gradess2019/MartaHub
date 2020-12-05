// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/StaticMeshContainer.h"

#include "PhysicalActorInfo.generated.h"

/**
 * Data asset for physical actors such as cup, table, armchair, etc.
 */
UCLASS(Blueprintable, BlueprintType)
class MARTAHUB_API UPhysicalActorInfo : public UDataAsset, public IStaticMeshContainer
{
	GENERATED_BODY()

public:

	virtual void SetStaticMesh_Implementation(UStaticMesh* InStaticMesh) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Mass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* Mesh;
};
