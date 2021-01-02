// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnapshotBase.h"
#include "Interfaces/Restorers/ComponentSaver.h"

#include "ComponentPhysicsSnapshot.generated.h"

/**
 * 
 */
UCLASS()
class MARTAHUB_API UComponentPhysicsSnapshot : public USnapshotBase, public IComponentSaver
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Component Physics Snapshot")
	UPrimitiveComponent* Component;

	UPROPERTY(BlueprintReadWrite, Category = "Component Physics Snapshot")
	bool bSimulatePhysics;

	UPROPERTY(BlueprintReadWrite, Category = "Component Physics Snapshot")
	TEnumAsByte<ECollisionEnabled::Type> CollisionType;

public:
	
	virtual bool Save_Implementation(UActorComponent* InComponent) override;
	
	// IRestorer implementation begin
	virtual void Restore_Implementation() override;
	// IRestorer implementation end

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Component Physics Snapshot")
	void RestoreOnlyCollision();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Component Physics Snapshot")
	void RestoreOnlyPhysics();
};
