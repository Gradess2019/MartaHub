// Gradess Games. All rights reserved.

#include "Factories/DefaultSnapshotFactory.h"

#include "Snapshots/ActorPhysicsSnapshot.h"


USnapshotBase* UDefaultSnapshotFactory::CreateSnapshot_Implementation(TSubclassOf<USnapshotBase> Class)
{
	if (Class->IsChildOf(UComponentPhysicsSnapshot::StaticClass()))
	{
		return Execute_CreateComponentPhysicsSnapshot(this);
	}

	if (Class->IsChildOf(UActorPhysicsSnapshot::StaticClass()))
	{
		return Execute_CreateActorPhysicsSnapshot(this);
	}

	return nullptr;
}

USnapshotBase* UDefaultSnapshotFactory::CreateComponentPhysicsSnapshot_Implementation()
{
	return NewObject<UComponentPhysicsSnapshot>();
}

USnapshotBase* UDefaultSnapshotFactory::CreateActorPhysicsSnapshot_Implementation()
{
	return NewObject<UActorPhysicsSnapshot>();

}
