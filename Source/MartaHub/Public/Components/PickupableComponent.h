// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupableComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPickupableComponent, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API UPickupableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickupableComponent();

protected:

	UPROPERTY(BlueprintReadWrite)
	FVector Offset;

	UPROPERTY(BlueprintReadWrite)
	float CachedBound;

	UPROPERTY()
	class UStaticMeshComponent* Parent;

	virtual void BeginPlay() override;

	UFUNCTION(
		BlueprintCallable, 
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	bool SetupParent();

	UFUNCTION(
		BlueprintCallable, 
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void SetupOffset();

	UFUNCTION(
		BlueprintCallable, 
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void CacheBound();
};
