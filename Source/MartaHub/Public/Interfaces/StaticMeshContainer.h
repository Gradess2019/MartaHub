// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StaticMeshContainer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStaticMeshContainer : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents an object that contains static mesh
 */
class MARTAHUB_API IStaticMeshContainer
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Static Mesh Container")
	void SetStaticMesh(UPARAM(DisplayName="Static Mesh") class UStaticMesh* InStaticMesh);
};
