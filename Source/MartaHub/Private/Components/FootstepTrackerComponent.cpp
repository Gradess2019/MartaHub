// Gradess Games. All rights reserved.

#include "Components/FootstepTrackerComponent.h"


#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogFootstepTracker);

UFootstepTrackerComponent::UFootstepTrackerComponent()
{
	Rate = 0.5f;
	VelocityThreshold = 27000.f;
	TraceDistance = 100.f;
}

void UFootstepTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent = GetOwner()->FindComponentByClass<UNavMovementComponent>();
	if (!IsValid(MovementComponent))
	{
		UE_LOG(LogFootstepTracker, Error, TEXT("Actor doesn't have movement component"));
	}

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UFootstepTrackerComponent::Track, Rate, true);
}

void UFootstepTrackerComponent::Track_Implementation()
{
	const auto bOnGround = MovementComponent->IsMovingOnGround();
	const auto bEnoughVelocity = MovementComponent->Velocity.SizeSquared() > VelocityThreshold;

	auto Hit = FHitResult();
	
	const auto StartLocation = GetOwner()->GetActorLocation();
	const auto DownDirection = GetOwner()->GetActorUpVector() * -1.f;

	const auto EndLocation = StartLocation + DownDirection * TraceDistance;

	const auto TraceTag = FName("FootstepTrace");
	const auto bTraceComplex = true;
	const auto IgnoreActor = GetOwner();
	auto QueryParams = FCollisionQueryParams(TraceTag, bTraceComplex, IgnoreActor);
	QueryParams.bReturnPhysicalMaterial = true;

	const auto bHitAny = GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
	);

	if (bOnGround && bEnoughVelocity && bHitAny)
	{
		OnStepTracked.Broadcast(Hit);
	}
}
