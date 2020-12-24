// Gradess Games. All rights reserved.

// ReSharper disable CppRedundantQualifier
#include "Snapshots/ActorPhysicsSnapshot.h"

bool UActorPhysicsSnapshot::Save_Implementation(AActor* InActor)
{
	const auto bSuccess = Super::Save_Implementation(InActor);
	if (!bSuccess) { return bSuccess; }

	TArray<UPrimitiveComponent*> ActorComponents;
	GetPrimitiveComponents(ActorComponents);
	CreateComponentPhysicsSnapshots(ActorComponents);

	return true;
}

void UActorPhysicsSnapshot::GetPrimitiveComponents_Implementation(TArray<UPrimitiveComponent*>& OutComponents)
{
	const auto bIncludeFromChildActors = true;
	Actor->GetComponents<UPrimitiveComponent>(OutComponents, bIncludeFromChildActors);
}

void UActorPhysicsSnapshot::CreateComponentPhysicsSnapshots_Implementation(const TArray<UPrimitiveComponent*>& ActorComponents)
{
	for (auto Component : ActorComponents)
	{
		auto Snapshot = NewObject<UComponentPhysicsSnapshot>();
		Snapshot->Save(Component);
		Snapshots.Add(Snapshot);
	}
}

void UActorPhysicsSnapshot::Restore_Implementation()
{
	for (auto Snapshot : Snapshots)
	{
		Execute_Restore(Snapshot);
	}
}
