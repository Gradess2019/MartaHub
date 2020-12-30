// Gradess Games. All rights reserved.


#include "Components/ObjectSelectorComponent.h"

#include "Interfaces/Selectable.h"
#include "Kismet/KismetSystemLibrary.h"

class UCameraComponent;

UObjectSelectorComponent::UObjectSelectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1f;

	TraceDistance = 200.f;
}

void UObjectSelectorComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto bStandalone = UKismetSystemLibrary::IsStandalone(this);
	
	if (!bStandalone && !GetOwner()->HasLocalNetOwner())
	{
		Deactivate();
		return;
	}
	SetupQueryParams();
	SetupCamera();
}

void UObjectSelectorComponent::Deactivate()
{
	Super::Deactivate();
	SetComponentTickEnabled(false);
	DisableSelectedActor();
}

void UObjectSelectorComponent::SetupQueryParams_Implementation()
{
	QueryParams = FCollisionQueryParams();
	QueryParams.AddIgnoredActor(GetOwner());
}

void UObjectSelectorComponent::SetupCamera_Implementation()
{
	TArray<UCameraComponent*> CameraComponents;
	GetOwner()->GetComponents<UCameraComponent>(CameraComponents);
	if (CameraComponents.Num() == 0)
	{
		// TODO: Replace with BPFL
		UE_LOG(LogTemp, Error, TEXT("%s: Doesn't have a UCameraComponent!"), *GetOwner()->GetName());
	}
	else
	{
		Camera = CameraComponents[0];
	}
}

void UObjectSelectorComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateState();
}

void UObjectSelectorComponent::UpdateState_Implementation()
{
	const auto NewActor = LineTrace();

	if (!IsAppropriateActor(NewActor))
	{
		DisableSelectedActor();
		return;
	}

	DisableSelectedActor();

	ISelectable::Execute_Select(NewActor);
	SelectedActor = NewActor;
}

AActor* UObjectSelectorComponent::LineTrace_Implementation() const
{
	auto Hit = FHitResult();
	const auto Start = Camera->GetComponentLocation();
	const auto Offset = Camera->GetForwardVector() * TraceDistance;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		Offset + Start,
		ECC_Visibility,
		QueryParams
	);

	return Hit.GetActor();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool UObjectSelectorComponent::IsAppropriateActor_Implementation(const AActor* NewActor)
{
	return IsValid(NewActor) && NewActor->Implements<USelectable>();
}

void UObjectSelectorComponent::DisableSelectedActor_Implementation()
{
	if (!IsValid(SelectedActor)) { return; }
	ISelectable::Execute_Unselect(SelectedActor);
	SelectedActor = nullptr;
}
