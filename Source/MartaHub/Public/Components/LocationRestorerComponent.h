// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseRestorerComponent.h"
#include "Snapshots/ActorPhysicsSnapshot.h"

#include "LocationRestorerComponent.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API ULocationRestorerComponent : public UBaseRestorerComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Position Restorer")
	FVector InitialLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Position Restorer")
	FVector StartLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Position Restorer")
	UActorPhysicsSnapshot* Snapshot;
	
	virtual void BeginPlay() override;

public:

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

protected:

	UFUNCTION()
	void UpdateElapsedTime(float DeltaTime);

	UFUNCTION()
	void UpdateLocation() const;

	UFUNCTION()
	void CompleteRestoring();

	// Restorer interface begin
	virtual void Restore_Implementation() override;
	// Restorer interface end
	
	UFUNCTION()
	void CreateSnapshot(AActor* Owner);

	UFUNCTION()
	void DisablePhysicsAndCollision() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
