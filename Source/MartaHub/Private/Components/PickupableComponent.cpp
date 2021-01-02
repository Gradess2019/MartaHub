// Gradess Games. All rights reserved.

#include "Components/PickupableComponent.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Libraries/PickupHelper.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogPickupableComponent);

UPickupableComponent::UPickupableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	PickupProfileName = FName("PickupedActor");
	ClearProfileName = FName("PhysicsActor");

	ClassFilter = AActor::StaticClass();

	CheckOverlapsRate = 0.1f;
	InterpolationSpeed = 10.f;

	SetIsReplicatedByDefault(true);
	SetNetAddressable();
}

void UPickupableComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto bSuccess = SetupRoot();
	if (!bSuccess) { return; }

	const auto bServer = GetOwner()->HasAuthority();
	if (bServer)
	{
		SetupOffset();
		CacheBound();
	}
}

bool UPickupableComponent::SetupRoot_Implementation()
{
	Root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (!IsValid(Root))
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
	Root->GetLocalBounds(Min, Max);

	CachedBound = FMath::Abs(Min.X) + FMath::Abs(Max.X);
}

void UPickupableComponent::CheckOverlaps_Implementation()
{
	TArray<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OverlappingActors, ClassFilter);

	const auto Length = OverlappingActors.Num();
	if (Length > 0) { return; }

	ClearCheckOverlapsTimer();
	Root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Root->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
}

void UPickupableComponent::ClearCheckOverlapsTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(CheckOverlapsTimer);
}

// IPickupable begin
void UPickupableComponent::SetPickupLocation_Implementation(const FVector& OwnerLocation, const FVector& OwnerDirection)
{
	auto Target = GetOwner();
	const auto Alpha = UGameplayStatics::GetWorldDeltaSeconds(this) * InterpolationSpeed;

	const auto Location = UPickupHelper::CalculatePickupLocation(
		Target,
		OwnerLocation,
		OwnerDirection,
		Offset,
		CachedBound,
		Alpha
	);

	const auto Rotation = UPickupHelper::CalculatePickupRotation(
		Target,
		OwnerDirection,
		Alpha
	);

	Target->SetActorLocation(Location);
	Target->SetActorRotation(Rotation);
}

void UPickupableComponent::PreparePickup_Implementation()
{
	const auto bStandalone = UKismetSystemLibrary::IsStandalone(this);
	if (bStandalone)
	{
		ClientPreparePickup();
	}
	else
	{
		ServerPreparePickup();
	}
}

void UPickupableComponent::ClearPickup_Implementation()
{
	const auto bStandalone = UKismetSystemLibrary::IsStandalone(this);
	if (bStandalone)
	{
		ClientClearPickup();
	}
	else
	{
		ServerClearPickup();
	}
}

void UPickupableComponent::Throw_Implementation(float Force)
{
	if (!IsValid(Root)) { return; }
	const auto Direction = GetOwner()->GetActorForwardVector();
	const auto TotalForce = Root->GetMass() * Force;
	const auto Impulse = TotalForce * Direction;
	Root->AddImpulse(Impulse);
}

// IPickupable end

// PrepareForPickup() RPCs

void UPickupableComponent::ClientPreparePickup_Implementation()
{
	if (!IsValid(Root)) { return; }
	Root->SetSimulatePhysics(false);
	Root->SetCollisionProfileName(PickupProfileName);

	Root->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Root->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	const auto bLoop = true;
	GetWorld()->GetTimerManager().SetTimer(
		CheckOverlapsTimer,
		this,
		&UPickupableComponent::CheckOverlaps,
		CheckOverlapsRate,
		bLoop
	);
}

void UPickupableComponent::ServerPreparePickup_Implementation()
{
	MulticastPreparePickup();
	GetOwner()->SetReplicates(false);
}

bool UPickupableComponent::ServerPreparePickup_Validate()
{
	return true;
}

void UPickupableComponent::MulticastPreparePickup_Implementation()
{
	ClientPreparePickup();
}

// ClearPickup() RPCs

void UPickupableComponent::ClientClearPickup_Implementation()
{
	if (!IsValid(Root)) { return; }
	Root->SetSimulatePhysics(true);
	Root->SetCollisionProfileName(ClearProfileName);
	Root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ClearCheckOverlapsTimer();
}

void UPickupableComponent::ServerClearPickup_Implementation()
{
	GetOwner()->SetReplicates(true);
	MulticastClearPickup();
}

bool UPickupableComponent::ServerClearPickup_Validate()
{
	return true;
}

void UPickupableComponent::MulticastClearPickup_Implementation()
{
	ClientClearPickup();
}

void UPickupableComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UPickupableComponent, Offset, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(UPickupableComponent, CachedBound, COND_InitialOnly);
}
