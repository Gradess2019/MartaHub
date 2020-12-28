// Gradess Games. All rights reserved.

#include "Snapshots/SnapshotBase.h"

void USnapshotBase::Take_Implementation()
{
	ReferenceCount++;
}

void USnapshotBase::Release_Implementation()
{
	if (ReferenceCount < 0) { return; }

	ReferenceCount--;
}

bool USnapshotBase::CanRestore_Implementation()
{
	return ReferenceCount == 1;
}

int USnapshotBase::GetReferenceCount_Implementation()
{
	return ReferenceCount;
}
