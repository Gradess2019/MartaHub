// Gradess Games. All rights reserved.

#include "States/BaseState.h"

UWorld* UBaseState::GetWorld() const
{
	if (HasAllFlags(RF_ClassDefaultObject))
	{
		return nullptr;
	}
	return GetOuter()->GetWorld();
}
