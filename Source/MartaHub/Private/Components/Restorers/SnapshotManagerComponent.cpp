// Gradess Games. All rights reserved.

#include "Components/Restorers/SnapshotManagerComponent.h"
#include "Factories/DefaultSnapshotFactory.h"
#include "Interfaces/Factories/SnapshotFactory.h"
#include "Interfaces/Restorers/ActorSaver.h"
#include "Snapshots/SnapshotBase.h"

USnapshotManagerComponent::USnapshotManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DefaultSnapshotFactoryClass = UDefaultSnapshotFactory::StaticClass();
}

void USnapshotManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(DefaultSnapshotFactoryClass)) { return; }
	SnapshotFactory = NewObject<UObject>(this, DefaultSnapshotFactoryClass);
}

USnapshotBase* USnapshotManagerComponent::TakeSnapshot_Implementation(const TSubclassOf<USnapshotBase> Class)
{
	const auto SnapshotPtr = Snapshots.Find(Class);
	USnapshotBase* Snapshot;

	if (!SnapshotPtr) { 
		const auto NewSnapshot = ISnapshotFactory::Execute_CreateSnapshot(SnapshotFactory.GetObject(), Class);
		if (!IsValid(NewSnapshot)) { return nullptr; }
		const auto bImplements = NewSnapshot->Implements<UActorSaver>();
		if (bImplements)
		{
			IActorSaver::Execute_Save(NewSnapshot, GetOwner());
		}

		Snapshots.Add(NewSnapshot->GetClass(), NewSnapshot);
		Snapshot = NewSnapshot;
	} else
	{
		Snapshot = *SnapshotPtr;
	}

	Snapshot->Take();
	return Snapshot;
}

void USnapshotManagerComponent::ReleaseSnapshot_Implementation(USnapshotBase* Snapshot)
{
	if (!IsValid(Snapshot)) { return; }
	
	const auto Key = Snapshot->GetClass();
	const auto bContains = Snapshots.Contains(Key);
	if (!bContains) { return; }

	Snapshot->Release();

	// Destroy snapshot with zero references
	if (Snapshot->GetReferenceCount() == 0)
	{
		Snapshots.Remove(Key);
		Snapshot->MarkPendingKill();
	}
}
