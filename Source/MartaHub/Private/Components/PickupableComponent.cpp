// Gradess Games. All rights reserved.

#include "Components/PickupableComponent.h"

DEFINE_LOG_CATEGORY(LogPickupableComponent);

UPickupableComponent::UPickupableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickupableComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto bSuccess = SetupParent();
	if (!bSuccess) { return; }
	
	SetupOffset();
	CacheBound();
}

bool UPickupableComponent::SetupParent_Implementation()
{
	Parent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (!IsValid(Parent))
	{
		UE_LOG(LogPickupableComponent, Error, TEXT("RootComponent isn't UStaticMeshComponent!"));
		DestroyComponent();
		return false;
	}
	
	return true;
}

void UPickupableComponent::SetupOffset_Implementation()
{
	const auto Location = GetOwner()->GetActorLocation();
	auto Origin = FVector();
	auto Extent = FVector();

	GetOwner()->GetActorBounds(false, Origin, Extent);

	Offset = Location - Origin;
}

void UPickupableComponent::CacheBound_Implementation()
{
	auto Min = FVector();
	auto Max = FVector();
	Parent->GetLocalBounds(Min, Max);

	CachedBound = FMath::Abs(Min.X) + FMath::Abs(Max.X);
}