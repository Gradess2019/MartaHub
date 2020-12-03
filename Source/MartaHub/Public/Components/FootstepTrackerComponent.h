// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FootstepTrackerComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFootstepTracker, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepTracked, const FHitResult&, Hit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API UFootstepTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFootstepTrackerComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker")
	float Rate;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Tracker")
	float VelocityThreshold;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Tracker")
	float TraceDistance;

	UPROPERTY(BlueprintReadWrite, Category = "Tracker | Footstep Tracker Component")
	UNavMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Tracker | Footstep Tracker Component")
	FTimerHandle Timer;

	UPROPERTY(BlueprintAssignable, Category = "Tracker | Footstep Tracker Component")
	FOnStepTracked OnStepTracked;

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Tracker | Footstep Tracker Component"
	)
	void Track();
};
