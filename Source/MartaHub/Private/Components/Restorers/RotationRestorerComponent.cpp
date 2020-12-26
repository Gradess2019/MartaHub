// Gradess Games. All rights reserved.

#include "Components/Restorers/RotationRestorerComponent.h"
#include "Interfaces/Restorers/Restorable.h"
#include "Interfaces/Snapshots/SnapshotManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/RestorerHelper.h"
#include "Net/UnrealNetwork.h"
#include "Snapshots/ActorPhysicsSnapshot.h"

void URotationRestorerComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto Owner = GetOwner();
	if (Owner->HasAuthority())
	{
		InitialRotation = Owner->GetActorRotation();
	}
}

void URotationRestorerComponent::UpdateRestoring_Implementation()
{
	const auto Alpha = GetAlpha();
	const auto bShortestPath = true;
	const auto NewRotation = UKismetMathLibrary::RLerp(
		StartRotation,
		InitialRotation,
		Alpha,
		bShortestPath
	);

	GetOwner()->SetActorRotation(NewRotation);
}

void URotationRestorerComponent::ClientRestore_Implementation()
{
	if (bRunning) { return; }
	Super::ClientRestore_Implementation();

	const auto Owner = GetOwner();
	URestorerHelper::DisablePhysicsAndCollision(Owner);
	StartRotation = Owner->GetActorRotation();
}

void URotationRestorerComponent::SetupSnapshot(AActor* Owner)
{
	if (Owner->GetClass()->ImplementsInterface(URestorable::StaticClass()))
	{
		const auto Manager = IRestorable::Execute_GetSnapshotManager(Owner);
		Snapshot = Manager->Execute_TakeSnapshot(Manager.GetObject(), UActorPhysicsSnapshot::StaticClass());
	}
}

void URotationRestorerComponent::GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(URotationRestorerComponent, InitialRotation, COND_InitialOnly);
}
