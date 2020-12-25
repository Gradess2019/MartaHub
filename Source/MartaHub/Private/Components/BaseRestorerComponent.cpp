// Gradess Games. All rights reserved.

#include "Components/BaseRestorerComponent.h"
#include "Snapshots/SnapshotBase.h"

UBaseRestorerComponent::UBaseRestorerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(true);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloatAsset(TEXT("CurveFloat'/Game/MartaHub/Curves/Curve_DefaultLerp_Float.Curve_DefaultLerp_Float'"));
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
	Execute_Restore(Snapshot);
	Snapshot = nullptr;
}

void UBaseRestorerComponent::Restore_Implementation()
{
	if (bRunning) { return; }
	bRunning = true;
	SetComponentTickEnabled(true);

	const auto Owner = GetOwner();
	CreateSnapshot(Owner);
}

void UBaseRestorerComponent::CreateSnapshot(AActor* Actor)
{
	unimplemented();
}

float UBaseRestorerComponent::GetAlpha() const
{
	return Lerp->GetFloatValue(ElapsedTime);
}


