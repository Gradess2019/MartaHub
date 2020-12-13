// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateColor.h"
#include "UserInterfaceDataAsset.generated.h"

/**
 * Data asset for UI style
 */
UCLASS(Blueprintable, BlueprintType)
class USERINTERFACEPACK_API UUserInterfaceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Style")
	FSlateColor PrimaryColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Style")
	FSlateColor SecondaryColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Style")
	FSlateColor TertiaryColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Style")
	FSlateColor PrimaryTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Style")
	FSlateColor SecondaryTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Style")
	FSlateColor AccentColor;
};
