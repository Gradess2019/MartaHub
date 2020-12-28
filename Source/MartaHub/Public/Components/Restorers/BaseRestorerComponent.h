// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Restorer.h"
#include "BaseRestorerComponent.generated.h"

class USnapshotBase;

DECLARE_LOG_CATEGORY_EXTERN(LogRestorerComponent, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestoringComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRestoringUpdate, float, Alpha);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable)
class MARTAHUB_API UBaseRestorerComponent : public UActorComponent, public IRestorer
{
	GENERATED_BODY()

public:

	UBaseRestorerComponent();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Base Restorer Component")
	UCurveFloat* Lerp;

	UPROPERTY(BlueprintReadWrite, Category = "Base Restorer Component")
	float ElapsedTime;

	UPROPERTY(BlueprintReadWrite, Category = "Base Restorer Component")
	bool bRunning;

	UPROPERTY(BlueprintReadWrite, Category = "Base Restorer Component")
	USnapshotBase* Snapshot;

	UPROPERTY(BlueprintAssignable, Category = "Base Restorer Component")
	FRestoringComplete OnRestoringComplete;

	UPROPERTY(BlueprintAssignable, Category = "Base Restorer Component")
	FRestoringUpdate OnRestoringUpdate;

public:

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UFUNCTION()
	virtual void UpdateElapsedTime(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, Category = "Base Restorer Component")
	void UpdateRestoring();

	UFUNCTION(BlueprintCallable, Category = "Base Restorer Component")
	void CompleteRestoring();

public:

	virtual void Restore_Implementation() override;

protected:
	
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Base Restorer Component"
	)
	void ClientRestore();

	UFUNCTION(
		BlueprintCallable,
		NetMulticast,
		Reliable,
		Category = "Base Restorer Component"
	)
	void MulticastRestore();

	// TODO: Add BlueprintNativeEvent
	UFUNCTION(BlueprintCallable, Category = "Base Restorer Component")
	virtual void SetupSnapshot(AActor* Owner);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Restorer Component")
	float GetAlpha() const;

	void PrintError(const FString Message, const char* FunctionName, const int& Line);
};
