// Gradess Games. All rights reserved.

#include "Components/LocationRestorerComponent.h"

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
	const auto Alpha = Lerp->GetFloatValue(ElapsedTime);
	const auto NewLocation = FMath::Lerp(StartLocation, InitialLocation, Alpha);

	const auto bSweep = false;
	const auto OutSweepHitResult = nullptr;
	Owner->SetActorLocation(NewLocation, bSweep, OutSweepHitResult, ETeleportType::ResetPhysics);
}

void ULocationRestorerComponent::Restore_Implementation()
{
	if (bRunning) { return; }
	Super::Restore_Implementation();
	
	URestorerHelper::DisablePhysicsAndCollision(GetOwner());
	StartLocation = GetOwner()->GetActorLocation();
}

void ULocationRestorerComponent::CreateSnapshot(AActor* Owner)
{
	// TODO: What about Object Pool pattern?
	auto NewSnapshot = NewObject<UActorPhysicsSnapshot>();
	NewSnapshot->Save(Owner);
	Snapshot = NewSnapshot;
}

void ULocationRestorerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(ULocationRestorerComponent, InitialLocation, COND_InitialOnly);
}
