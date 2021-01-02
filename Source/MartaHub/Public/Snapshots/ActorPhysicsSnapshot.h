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

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Actor Physics Snapshot")
	TArray<UComponentPhysicsSnapshot*> Snapshots;

public:
	virtual bool Save_Implementation(AActor* InActor) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Physics Snapshot")
	void GetPrimitiveComponents(TArray<UPrimitiveComponent*>& OutComponents);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Physics Snapshot")
	void CreateComponentPhysicsSnapshots(const TArray<UPrimitiveComponent*>& Array);

public:
	UFUNCTION(BlueprintCallable, Category = "Actor Physics Snapshot")
	void RestoreComponentsCollision();

	UFUNCTION(BlueprintCallable, Category = "Actor Physics Snapshot")
	void RestoreComponentsPhysics();

	// IRestorer implementation begin
	virtual void Restore_Implementation() override;
	// IRestorer implementation end

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor Physics Snapshot")
	void RestoreComponents();
};
