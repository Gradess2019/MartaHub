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

	GetOwner()->SetActorRotation(NewRotation, ETeleportType::ResetPhysics);
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
	const auto bImplements = Owner->Implements<URestorable>();
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
	}
	else
	{
		const auto Message = FString().Appendf(
			TEXT("%s doesn't implements IRestorable interface!"),
			*GetOwner()->GetName()
		);
		PrintError(Message, __FUNCTION__, __LINE__);
	}
}

void URotationRestorerComponent::GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(URotationRestorerComponent, InitialRotation, COND_InitialOnly);
}
