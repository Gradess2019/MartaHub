// Gradess Games. All rights reserved.

#include "Libraries/RestorerHelper.h"

void URestorerHelper::DisablePhysicsAndCollision(AActor* Actor, const bool bIncludeChildren)
{
	TArray<UPrimitiveComponent*> Components;
	Actor->GetComponents<UPrimitiveComponent>(Components, bIncludeChildren);
	
	for (auto Component : Components)
	{
		Component->SetSimulatePhysics(false);
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
