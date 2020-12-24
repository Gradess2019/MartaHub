// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Restorer.h"
#include "BaseRestorerComponent.generated.h"

class USnapshotBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable)
class MARTAHUB_API UBaseRestorerComponent : public UActorComponent, public IRestorer
{
	GENERATED_BODY()

public:

	UBaseRestorerComponent();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Restorer")
	UCurveFloat* Lerp;

	UPROPERTY(BlueprintReadWrite, Category = "Restorer")
	float ElapsedTime;

	UPROPERTY(BlueprintReadWrite, Category = "Restorer")
	bool bRunning;

	UPROPERTY(BlueprintReadWrite, Category = "Restorer")
	USnapshotBase* Snapshot;

public:

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UFUNCTION()
	virtual void UpdateElapsedTime(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, Category = "Restorer")
	void UpdateRestoring();

	UFUNCTION()
	void CompleteRestoring();
};
