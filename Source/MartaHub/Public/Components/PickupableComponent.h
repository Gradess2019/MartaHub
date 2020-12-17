// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Pickupable.h"
#include "PickupableComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPickupableComponent, Log, All);

class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API UPickupableComponent : public UActorComponent, public IPickupable
{
	GENERATED_BODY()

public:
	UPickupableComponent();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Pickupable Component")
	FVector Offset;

	UPROPERTY(BlueprintReadWrite, Category = "Pickupable Component")
	float CachedBound;

	UPROPERTY(BlueprintReadWrite, Category = "Pickupable Component")
	UStaticMeshComponent* Root;

	UPROPERTY(BlueprintReadWrite, Category = "Pickupable Component")
	FTimerHandle CheckOverlapsTimer;

	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Collision"
	)
	FName PickupProfileName;

	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Collision"
	)
	FName ClearProfileName;

	/** Class Filter for checking overlaps */
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Overlap"
	)
	TSubclassOf<AActor> ClassFilter;

	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Overlap"
	)
	float CheckOverlapsRate;

	/** SetPickupLocation interpolation speed. The higher, the faster */
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Interpolation"
	)
	float InterpolationSpeed;

	virtual void BeginPlay() override;

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	bool SetupRoot();

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

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void CheckOverlaps();

	UFUNCTION(
        BlueprintCallable,
        Category = "Pickupable Component"
    )
    void ClearCheckOverlapsTimer();

public:
	// IPickupable begin
	virtual void SetPickupLocation_Implementation(const FVector& OwnerLocation, const FVector& OwnerDirection) override;
	virtual void PreparePickup_Implementation() override;
	virtual void ClearPickup_Implementation() override;
	virtual void Throw_Implementation(float Force) override;
	// IPickupable end

protected:
	// IPickupable replication begin

	// PrepareForPickup() RPCs
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void ClientPreparePickup();

	UFUNCTION(
		BlueprintCallable,
		Server,
		WithValidation,
		Reliable
	)
	void ServerPreparePickup();

	UFUNCTION(
		BlueprintCallable,
		NetMulticast,
		Reliable
	)
	void MulticastPreparePickup();

	// ClearPickup() RPCs
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void ClientClearPickup();

	UFUNCTION(
		BlueprintCallable,
		Server,
		WithValidation,
		Reliable
	)
	void ServerClearPickup();

	UFUNCTION(
		BlueprintCallable,
		NetMulticast,
		Reliable
	)
	void MulticastClearPickup();
	// IPickupable replication end
};
