// Gradess Games. All rights reserved.

#include "Components/Restorers/BaseRestorerComponent.h"
#include "Interfaces/Snapshots/SnapshotManager.h"
#include "Interfaces/Restorers/Restorable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Snapshots/SnapshotBase.h"

UBaseRestorerComponent::UBaseRestorerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(true);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloatAsset(
		TEXT("CurveFloat'/Game/MartaHub/Curves/Curve_DefaultLerp_Float.Curve_DefaultLerp_Float'"));
	Lerp = CurveFloatAsset.Object;

	ElapsedTime = 0.f;
	bRunning = false;
}

void UBaseRestorerComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRunning)
	{
		UpdateElapsedTime(DeltaTime);
		UpdateRestoring();
	}
	else
	{
		CompleteRestoring();
	}
}

void UBaseRestorerComponent::UpdateElapsedTime(float DeltaTime)
{
	auto MinTime = 0.f;
	auto MaxTime = 0.f;
	Lerp->GetTimeRange(MinTime, MaxTime);
	bRunning = ElapsedTime < MaxTime;
	ElapsedTime += DeltaTime;
}

void UBaseRestorerComponent::UpdateRestoring_Implementation()
{
	unimplemented();
}

void UBaseRestorerComponent::CompleteRestoring()
{
	ElapsedTime = 0.f;
	SetComponentTickEnabled(false);

	if (!IsValid(Snapshot)) { return; }
	if (Snapshot->CanRestore())
	{
		Execute_Restore(Snapshot);

		OnRestoringComplete.Broadcast();
	}

	const auto Owner = GetOwner();
	const auto Manager = IRestorable::Execute_GetSnapshotManager(Owner);
	Manager->Execute_ReleaseSnapshot(Manager.GetObject(), Snapshot);

	Snapshot = nullptr;
}

void UBaseRestorerComponent::Restore_Implementation()
{
	const auto bStandalone = UKismetSystemLibrary::IsStandalone(this);
	const auto bServer = UKismetSystemLibrary::IsServer(this);

	if (bStandalone)
	{
		ClientRestore();
	}
	else if (bServer)
	{
		MulticastRestore();
	}
}

void UBaseRestorerComponent::ClientRestore_Implementation()
{
	if (bRunning) { return; }
	bRunning = true;
	SetComponentTickEnabled(true);

	const auto Owner = GetOwner();
	SetupSnapshot(Owner);
}

void UBaseRestorerComponent::MulticastRestore_Implementation()
{
	ClientRestore();
}

void UBaseRestorerComponent::SetupSnapshot(AActor* Owner)
{
	unimplemented();
}

float UBaseRestorerComponent::GetAlpha() const
{
	return Lerp->GetFloatValue(ElapsedTime);
}
