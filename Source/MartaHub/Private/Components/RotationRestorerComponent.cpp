// Gradess Games. All rights reserved.

#include "Components/RotationRestorerComponent.h"


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

void URotationRestorerComponent::Restore_Implementation()
{
	if (bRunning) { return; }
	Super::Restore_Implementation();

	const auto Owner = GetOwner();
	URestorerHelper::DisablePhysicsAndCollision(Owner);
	StartRotation = Owner->GetActorRotation();
}

void URotationRestorerComponent::CreateSnapshot(AActor* Actor)
{
	// FIXME Replace with Actor->GetSnapshot();
	// const auto NewSnapshot = NewObject<UActorPhysicsSnapshot>();
	// NewSnapshot->Save(Actor);
	// Snapshot = NewSnapshot;
}

void URotationRestorerComponent::GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(URotationRestorerComponent, InitialRotation, COND_InitialOnly);
}
