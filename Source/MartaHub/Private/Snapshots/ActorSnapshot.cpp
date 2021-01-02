// Gradess Games. All rights reserved.

#include "Snapshots/ActorSnapshot.h"

bool UActorSnapshot::Save_Implementation(AActor* InActor)
{
	if (!IsValid(InActor)) { return false; }
	Actor = InActor;
	return true;
}
