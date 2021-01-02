// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserInterfaceStructs.h"
#include "Styling/SlateTypes.h"
#include "UserInterfaceHelper.generated.h"

class USizeBox;
class UBorder;
class UComboBoxString;
/**
 * UserInterfacePack helper
 */
UCLASS()
class USERINTERFACEPACK_API UUserInterfaceHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Set Tint param in Slate Brush */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Style")
	static void SetTint(
		UPARAM(ref) FSlateBrush& SlateBrush,
		const FSlateColor Color
	);

	/** Set button tints using style reference */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Style | Button")
	static void SetButtonTint(
		UPARAM(ref) FButtonStyle& ButtonStyle,
		const FButtonColorData ColorData
	);

	/** Set combo box tints using widget */
	UFUNCTION(
		BlueprintCallable,
		Category = "UI Helper | Style | Combo Box",
		meta = (HidePin = "OwnerWidget", DefaultToSelf = "OwnerWidget")
	)
	static void SetComboBoxTintWidget(
		UUserWidget* OwnerWidget,
		UComboBoxString* ComboBox,
		const FComboBoxColorData ColorData
	);

	/** Set combo box tints using style reference */
	UFUNCTION(
		BlueprintCallable,
		Category = "UI Helper | Style | Combo Box",
		meta = (HidePin = "OwnerWidget", DefaultToSelf = "OwnerWidget")
	)
	static void SetComboBoxTint(
		UUserWidget* OwnerWidget,
		UPARAM(ref) FComboButtonStyle& ComboButtonStyle,
		FTableRowStyle& ItemStyle,
		const FComboBoxColorData ColorData
	);

	/** Set border tint using widget */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Style | Border")
	static void SetBorderTintWidget(UBorder* Border, const FSlateColor Color);

	/** Set check box tints using style reference */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Style | Check Box")
	static void SetCheckBoxTint(
		UPARAM(ref) FCheckBoxStyle& CheckBoxStyle,
		const FCheckBoxColorData ColorData
	);

	/** Set progress bar tints using style reference */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Style | Progress Bar")
	static void SetProgressBarTint(
		UPARAM(ref) FProgressBarStyle& ProgressBarStyle,
		const FProgressBarColorData ColorData
	);

	/** Set slider tints using style reference */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Style | Slider")
	static void SetSliderTint(
		UPARAM(ref) FSliderStyle& SliderStyle,
		const FSliderColorData ColorData
	);

	/** Set size overrides of USizeBox */
	UFUNCTION(BlueprintCallable, Category = "UI Helper | Size box")
	static void SetSize(USizeBox* SizeBox, float Width, float Height);
};
