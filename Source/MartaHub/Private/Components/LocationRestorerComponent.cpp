// Gradess Games. All rights reserved.

#include "Components/LocationRestorerComponent.h"
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
	bRunning = true;

	const auto Owner = GetOwner();

	CreateSnapshot(Owner);
	DisablePhysicsAndCollision();

	StartLocation = Owner->GetActorLocation();
	SetComponentTickEnabled(true);
}

void ULocationRestorerComponent::CreateSnapshot(AActor* const Owner)
{
	// TODO: What about Object Pool pattern?
	auto NewSnapshot = NewObject<UActorPhysicsSnapshot>();
	NewSnapshot->Save(Owner);
	Snapshot = NewSnapshot;
}

void ULocationRestorerComponent::DisablePhysicsAndCollision() const
{
	const auto Owner = GetOwner();

	// TODO: Add disabling physics and collision to RestorerHelper
	TArray<UPrimitiveComponent*> Components;
	const auto bIncludeFromChildActors = true;
	Owner->GetComponents<UPrimitiveComponent>(Components, bIncludeFromChildActors);

	for (auto Component : Components)
	{
		Component->SetSimulatePhysics(false);
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ULocationRestorerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(ULocationRestorerComponent, InitialLocation, COND_InitialOnly);
}
