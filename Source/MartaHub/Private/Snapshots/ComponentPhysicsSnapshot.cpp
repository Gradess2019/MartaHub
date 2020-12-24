// Gradess Games. All rights reserved.

#include "Snapshots/ComponentPhysicsSnapshot.h"

bool UComponentPhysicsSnapshot::Save(UPrimitiveComponent* InComponent)
{
	if (!IsValid(InComponent)) { return false; }

	Component = InComponent;
	bSimulatePhysics = InComponent->IsSimulatingPhysics();
	CollisionType = InComponent->GetCollisionEnabled();
	return true;
}

void UComponentPhysicsSnapshot::Restore_Implementation()
{
	Component->SetSimulatePhysics(bSimulatePhysics);
	Component->SetCollisionEnabled(CollisionType);
}
