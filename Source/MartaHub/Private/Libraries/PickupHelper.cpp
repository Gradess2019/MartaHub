// Gradess Games. All rights reserved.


#include "Libraries/PickupHelper.h"

#include "Kismet/KismetMathLibrary.h"

FVector UPickupHelper::CalculatePickupLocation(
	AActor* Target,
	const FVector OwnerLocation,
	const FVector OwnerDirection,
	const FVector Offset,
	const float Bound,
	const float Alpha
)
{
	if (!IsValid(Target)) { return FVector::ZeroVector; }

	const auto CurrentLocation = Target->GetActorLocation();
	const auto TargetLocation = OwnerDirection * Bound + OwnerLocation + Offset;
	const auto ResultLocation = FMath::Lerp(CurrentLocation, TargetLocation, Alpha);

	return ResultLocation;
}


FRotator UPickupHelper::CalculatePickupRotation(
	AActor* Target,
	const FVector OwnerDirection,
	const float Alpha
)
{
	if (!IsValid(Target)) { return FRotator::ZeroRotator; }

	const auto CurrentRotation = Target->GetActorRotation();
	const auto TargetRotation = OwnerDirection.Rotation();
	const auto bShortestPath = true;

	const auto ResultRotation = UKismetMathLibrary::RLerp(
		CurrentRotation,
		TargetRotation,
		Alpha,
		bShortestPath
	);

	return ResultRotation;
}
