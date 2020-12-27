// Gradess Games. All rights reserved.

#include "Components/Restorers/LocationRestorerComponent.h"
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

void ULocationRestorerComponent::ClientRestore_Implementation()
{
	if (bRunning) { return; }
	Super::ClientRestore_Implementation();

	const auto Owner = GetOwner();
	URestorerHelper::DisablePhysicsAndCollision(Owner);
	StartLocation = Owner->GetActorLocation();
}

// FIXME: Code duplication. See URotationRestorerComponent
void ULocationRestorerComponent::SetupSnapshot(AActor* Owner)
{
	const auto bImplements = Owner->Implements<URestorable>();
	// TODO: What about Object Pool pattern?
	if (bImplements)
	{
		auto Manager = IRestorable::Execute_GetSnapshotManager(Owner);
		if (!Manager)
		{
			const auto Message = FString().Appendf(
				TEXT("%s doesn't return ISnapshotManager. Check GetSnapshotManager()!"),
				*GetOwner()->GetName()
			);
			PrintError(Message, __FUNCTION__, __LINE__);
		}
		else
		{
			Snapshot = Manager->Execute_TakeSnapshot(Manager.GetObject(), UActorPhysicsSnapshot::StaticClass());
		}
	} else
	{
		const auto Message = FString().Appendf(
            TEXT("%s doesn't implements IRestorable interface!"),
            *GetOwner()->GetName()
        );
		PrintError(Message, __FUNCTION__, __LINE__);
	}
}

void ULocationRestorerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ULocationRestorerComponent, InitialLocation, COND_InitialOnly);
}
