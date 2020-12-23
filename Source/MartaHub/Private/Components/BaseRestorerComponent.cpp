// Gradess Games. All rights reserved.

#include "Components/BaseRestorerComponent.h"

UBaseRestorerComponent::UBaseRestorerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(true);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloatAsset(TEXT("CurveFloat'/Game/MartaHub/Curves/Curve_DefaultLerp_Float.Curve_DefaultLerp_Float'"));
	Lerp = CurveFloatAsset.Object;
}
