// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Snapshots/SnapshotManager.h"
#include "SnapshotManagerComponent.generated.h"

class USnapshotBase;
class ISnapshotFactory;
class USnapshotFactory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API USnapshotManagerComponent : public UActorComponent, public ISnapshotManager
{
	GENERATED_BODY()

public:
	USnapshotManagerComponent();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Snapshot Manager")
	USnapshotBase* PhysicsSnapshot;

	UPROPERTY(BlueprintReadWrite, Category = "Snapshot Manager")
	TMap<TSubclassOf<USnapshotBase>, USnapshotBase*> Snapshots;

	UPROPERTY(EditDefaultsOnly, meta = (MustImplement = "SnapshotFactory"))
	TSubclassOf<UObject> DefaultSnapshotFactoryClass;

	UPROPERTY(BlueprintReadWrite, Category = "Snapshot Manager")
	TScriptInterface<ISnapshotFactory> SnapshotFactory;

	virtual void BeginPlay() override;

public:

	virtual USnapshotBase* TakeSnapshot_Implementation(TSubclassOf<USnapshotBase> Class) override;
	virtual void ReleaseSnapshot_Implementation(USnapshotBase* Snapshot) override;
};
