// Gradess Games. All rights reserved.

#include "Components/PositionRestorer.h"

UPositionRestorer::UPositionRestorer()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UPositionRestorer::BeginPlay()
{
	Super::BeginPlay();
}

void UPositionRestorer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

