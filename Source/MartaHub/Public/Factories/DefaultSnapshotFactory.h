// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Factories/SnapshotFactory.h"
#include "DefaultSnapshotFactory.generated.h"

/**
 * Default snapshot factory
 */
UCLASS()
class MARTAHUB_API UDefaultSnapshotFactory : public UObject, public ISnapshotFactory
{
	GENERATED_BODY()

public:

	virtual USnapshotBase* CreateSnapshot_Implementation(TSubclassOf<USnapshotBase> Class) override;
	virtual USnapshotBase* CreateComponentPhysicsSnapshot_Implementation() override;
	virtual USnapshotBase* CreateActorPhysicsSnapshot_Implementation() override;
};
