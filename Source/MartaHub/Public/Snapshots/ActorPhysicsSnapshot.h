// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentPhysicsSnapshot.h"
#include "Snapshots/ActorSnapshot.h"
#include "ActorPhysicsSnapshot.generated.h"

/**
 * Actor physics snapshot
 */
UCLASS(BlueprintType, Blueprintable)
class MARTAHUB_API UActorPhysicsSnapshot : public UActorSnapshot
{
	GENERATED_BODY()

public:

	virtual bool Save_Implementation(AActor* InActor) override;

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Physics Snapshot")
	void GetPrimitiveComponents(TArray<UPrimitiveComponent*>& OutComponents);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Physics Snapshot")
	void CreateComponentPhysicsSnapshots(const TArray<UPrimitiveComponent*>& Array);

public:

	// IRestorer implementation begin
	virtual void Restore_Implementation() override;
	// IRestorer implementation end

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Actor Physics Snapshot")
	TArray<UComponentPhysicsSnapshot*> Snapshots;
};
