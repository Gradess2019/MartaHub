// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnapshotBase.h"
#include "ComponentPhysicsSnapshot.generated.h"

/**
 * 
 */
UCLASS()
class MARTAHUB_API UComponentPhysicsSnapshot : public USnapshotBase
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
	virtual bool Save(UPrimitiveComponent* InComponent);
	
	// IRestorer implementation begin
	virtual void Restore_Implementation() override;
	// IRestorer implementation end
};
