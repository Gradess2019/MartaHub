// Gradess Games. All rights reserved.

#include "Components/LocationRestorerComponent.h"
#include "Interfaces/Restorers/Restorable.h"
#include "Interfaces/Snapshots/SnapshotManager.h"
#include "Libraries/RestorerHelper.h"
#include "Net/UnrealNetwork.h"

void ULocationRestorerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		InitialLocation = GetOwner()->GetActorLocation();
	}
}

void ULocationRestorerComponent::UpdateRestoring_Implementation()
{
	UpdateLocation();
}

void ULocationRestorerComponent::UpdateLocation_Implementation()
{
	const auto Owner = GetOwner();
	const auto Alpha = GetAlpha();
	const auto NewLocation = FMath::Lerp(StartLocation, InitialLocation, Alpha);

	const auto bSweep = false;
	const auto OutSweepHitResult = nullptr;
	Owner->SetActorLocation(NewLocation, bSweep, OutSweepHitResult, ETeleportType::ResetPhysics);
}

void ULocationRestorerComponent::Restore_Implementation()
{
	if (bRunning) { return; }
	Super::Restore_Implementation();

	const auto Owner = GetOwner();
	URestorerHelper::DisablePhysicsAndCollision(Owner);
	StartLocation = Owner->GetActorLocation();
}

void ULocationRestorerComponent::SetupSnapshot(AActor* Owner)
{
	// TODO: What about Object Pool pattern?
	if (Owner->GetClass()->ImplementsInterface(URestorable::StaticClass()))
	{
		auto Manager = IRestorable::Execute_GetSnapshotManager(Owner);
		Snapshot = Manager->Execute_TakeSnapshot(Manager.GetObject(), UActorPhysicsSnapshot::StaticClass());
	}
}

void ULocationRestorerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(ULocationRestorerComponent, InitialLocation, COND_InitialOnly);
}
