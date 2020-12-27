// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Restorers/BaseRestorerComponent.h"
#include "RotationRestorerComponent.generated.h"

/**
 * Rotation restorer
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MARTAHUB_API URotationRestorerComponent : public UBaseRestorerComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Rotation Restorer")
	FRotator InitialRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Rotation Restorer")
	FRotator StartRotation;

	virtual void BeginPlay() override;

public:
	virtual void UpdateRestoring_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Rotation Restorer")
	void SetReplicatedRotation(FRotator NewRotation) const;

	UFUNCTION(BlueprintCallable, Category = "Rotation Restorer")
	void ResetReplicatedRotation() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rotation Restorer")
	void GetReplicatedRotation(FRotator& Rotation, FVector& AngularVelocity) const;

protected:
	virtual void ClientRestore_Implementation() override;

	virtual void SetupSnapshot(AActor* Owner) override;
	virtual void GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
