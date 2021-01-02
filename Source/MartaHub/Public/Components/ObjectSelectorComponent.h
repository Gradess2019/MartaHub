// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "ObjectSelectorComponent.generated.h"

/**
 * Object selector that uses ISelectable interface
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API UObjectSelectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObjectSelectorComponent();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Object Selector Component")
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, Category = "Object Selector Component")
	float TraceDistance;

	UPROPERTY(BlueprintReadWrite, Category = "Object Selector Component")
	AActor* SelectedActor;

	FCollisionQueryParams QueryParams;

	virtual void BeginPlay() override;
	virtual void Deactivate() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Object Selector Component")
	void SetupQueryParams();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Object Selector Component")
	void SetupCamera();

public:
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Object Selector Component")
	void UpdateState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Object Selector Component")
	AActor* LineTrace() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Object Selector Component")
	bool IsAppropriateActor(const AActor* NewActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Object Selector Component")
	void DisableSelectedActor();

};
