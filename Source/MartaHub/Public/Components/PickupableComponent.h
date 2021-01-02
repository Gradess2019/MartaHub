// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Pickupable.h"
#include "PickupableComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPickupableComponent, Log, All);

class UStaticMeshComponent;

/**
 * Component that gets ability physical actors (e.g. AStaticMeshActor) to be pickuped by someone or something
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARTAHUB_API UPickupableComponent : public UActorComponent, public IPickupable
{
	GENERATED_BODY()

public:
	UPickupableComponent();

protected:

	/** Offset from pickup location */
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Pickupable Component")
	FVector Offset;

	/** Cached actor X bound */
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Pickupable Component")
	float CachedBound;

	/** Parent root */
	UPROPERTY(BlueprintReadWrite, Category = "Pickupable Component")
	UStaticMeshComponent* Root;

	/** Timer for CheckOverlaps() method */
	UPROPERTY(BlueprintReadWrite, Category = "Pickupable Component")
	FTimerHandle CheckOverlapsTimer;

	/** Collision profile name of the object, when it is pickuped */
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Collision"
	)
	FName PickupProfileName;

	/** Collision profile name of the object, when player releases it */
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

	/** Delay between CheckOverlaps() calling */
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Overlap"
	)
	float CheckOverlapsRate;

	/** SetPickupLocation() interpolation speed. The higher, the faster */
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "Pickupable Component | Interpolation"
	)
	float InterpolationSpeed;

	virtual void BeginPlay() override;

	/** Try to find and setup root */
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	bool SetupRoot();

	/** Calculates the offset of the actor */
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void SetupOffset();

	/** Calculates the X bound of the actor */
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void CacheBound();

	/** Check if there is any overlapping actor. If not, then enable collision */
	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Pickupable Component"
	)
	void CheckOverlaps();

	/** Clears and invalidates CheckOverlapsTimer */
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
