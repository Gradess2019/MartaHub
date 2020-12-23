#pragma once

#include "CoreMinimal.h"
#include "UserInterfaceStructs.generated.h"

USTRUCT(BlueprintType)
struct FButtonColorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Color")
	FSlateColor Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Color")
	FSlateColor Hovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Color")
	FSlateColor Pressed;
};

USTRUCT(BlueprintType)
struct FTableRowColorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Color")
	FSlateColor Active;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Color")
	FSlateColor ActiveHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Color")
	FSlateColor Inactive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Color")
	FSlateColor InactiveHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Color")
	FSlateColor EvenRowHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Style")
	FSlateColor OddRowHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Style")
	FSlateColor Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table Row Style")
	FSlateColor SelectedText;
};

USTRUCT(BlueprintType)
struct FComboBoxColorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Box Color")
	FSlateColor ForegroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Box Color")
	FButtonColorData Button;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Box Color")
	FSlateColor DownArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Box Color")
	FSlateColor MenuBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Box Color")
	FTableRowColorData Item;
};


USTRUCT(BlueprintType)
struct FCheckBoxColorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor Unchecked;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor UncheckedHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor UncheckedPressed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor Checked;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor CheckedHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor CheckedPressed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor Undetermined;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor UndeterminedHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor UndeterminedPressed;
};

USTRUCT(BlueprintType)
struct FProgressBarColorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor Background;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor Fill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor Marquee;
};

USTRUCT(BlueprintType)
struct FSliderColorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor NormalBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor HoveredBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor DisabledBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor NormalThumb;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check Box Color")
	FSlateColor HoveredThumb;
};
