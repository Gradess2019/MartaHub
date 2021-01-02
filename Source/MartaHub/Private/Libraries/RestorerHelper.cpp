// Gradess Games. All rights reserved.

#include "Libraries/RestorerHelper.h"

#include "UObject/ReferencerFinder.h"

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

int URestorerHelper::GetReferenceCount(UObject* Object)
{
	TArray<UObject*> ReferredToObjects;
	GetReferences(Object, ReferredToObjects);

	return ReferredToObjects.Num();
}

void URestorerHelper::GetReferences(UObject* Object, TArray<UObject*>& OutReferences)
{
	FReferenceFinder ObjectReferenceCollector(OutReferences, Object, true, false, true, false);
	ObjectReferenceCollector.FindReferences(Object);
}
