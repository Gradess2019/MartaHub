// Gradess Games. All rights reserved.

#include "Snapshots/ComponentPhysicsSnapshot.h"

bool UComponentPhysicsSnapshot::Save_Implementation(UActorComponent* InComponent)
{
	if (!IsValid(InComponent) || !InComponent->IsA(UPrimitiveComponent::StaticClass())) { return false; }

	Component = Cast<UPrimitiveComponent>(InComponent);
	bSimulatePhysics = Component->IsSimulatingPhysics();
	CollisionType = Component->GetCollisionEnabled();
	return true;
}

void UComponentPhysicsSnapshot::Restore_Implementation()
{
	Component->SetSimulatePhysics(bSimulatePhysics);
	Component->SetCollisionEnabled(CollisionType);
}

void UComponentPhysicsSnapshot::RestoreOnlyPhysics_Implementation()
{
	Component->SetSimulatePhysics(bSimulatePhysics);
}

void UComponentPhysicsSnapshot::RestoreOnlyCollision_Implementation()
{
	Component->SetCollisionEnabled(CollisionType);
}
