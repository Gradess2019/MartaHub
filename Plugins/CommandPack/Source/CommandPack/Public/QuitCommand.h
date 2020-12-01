// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "Kismet/KismetSystemLibrary.h"

#include "QuitCommand.generated.h"

USTRUCT(BlueprintType)
struct FQuitCommandData
{
	GENERATED_BODY()

	FQuitCommandData(
		APlayerController* InPlayerController = nullptr,
		const TEnumAsByte<EQuitPreference::Type>& InQuitPreference = EQuitPreference::Quit,
		bool bInIgnorePlatformRestrictions = false
	)
	{
		PlayerController = InPlayerController;
		QuitPreference = InQuitPreference;
		bIgnorePlatformRestrictions = bInIgnorePlatformRestrictions;
	}

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Quit Command")
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Quit Command")
	TEnumAsByte<EQuitPreference::Type> QuitPreference;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Quit Command")
	bool bIgnorePlatformRestrictions;
};

/**
 * Base command for quit game
 */
UCLASS()
class COMMANDPACK_API UQuitCommand : public UBaseCommand
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Command Pack | Quit Command",
		meta=(WorldContext = "InWorldContextObject", CallableWithoutWorldContext)
	)
	bool Init(
		UObject* InWorldContextObject,
		UPARAM(DisplayName="Data") FQuitCommandData InData
	);

	virtual void Execute_Implementation() override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Quit Command")
	FQuitCommandData Data;
};
