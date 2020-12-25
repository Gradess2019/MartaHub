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

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Location Restorer")
	FVector InitialLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Location Restorer")
	FVector StartLocation;

	virtual void BeginPlay() override;

	virtual void UpdateRestoring_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Location Restorer")
	void UpdateLocation();

	// Restorer interface begin
	virtual void Restore_Implementation() override;
	// Restorer interface end
	
	virtual void SetupSnapshot(AActor* Owner) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
