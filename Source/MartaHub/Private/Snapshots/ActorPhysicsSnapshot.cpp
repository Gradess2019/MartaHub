// Gradess Games. All rights reserved.

// ReSharper disable CppRedundantQualifier
#include "Snapshots/ActorPhysicsSnapshot.h"

#include "Kismet/KismetSystemLibrary.h"

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

void UActorPhysicsSnapshot::CreateComponentPhysicsSnapshots_Implementation(
	const TArray<UPrimitiveComponent*>& ActorComponents)
{
	for (auto Component : ActorComponents)
	{
		auto Snapshot = NewObject<UComponentPhysicsSnapshot>();
		IComponentSaver::Execute_Save(Snapshot, Component);
		Snapshots.Add(Snapshot);
	}
}

void UActorPhysicsSnapshot::Restore_Implementation()
{
	if (Actor)
	{
		const auto bStandalone = UKismetSystemLibrary::IsStandalone(Actor);
		const auto bServer = UKismetSystemLibrary::IsServer(Actor);
		const auto bClient = !bServer && ! bStandalone;
		if (bClient)
		{
			Actor->GetRootComponent()->SetMobility(EComponentMobility::Static);
			RestoreComponentsCollision();

			FTimerHandle TimerHandle;
			Actor->GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				this,
				&UActorPhysicsSnapshot::RestoreComponentsPhysics,
				1.f
			);
		} else
		{
			RestoreComponents();
		}
	}
}

void UActorPhysicsSnapshot::RestoreComponentsCollision()
{
	for (auto Snapshot : Snapshots)
	{
		Snapshot->RestoreOnlyCollision();
	}
}

void UActorPhysicsSnapshot::RestoreComponentsPhysics()
{
	Actor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	
	for (auto Snapshot : Snapshots)
	{
		Snapshot->RestoreOnlyPhysics();
	}
}

void UActorPhysicsSnapshot::RestoreComponents_Implementation()
{
	for (auto Snapshot : Snapshots)
	{
		Execute_Restore(Snapshot);
	}
}
