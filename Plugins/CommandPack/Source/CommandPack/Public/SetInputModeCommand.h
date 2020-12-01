// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "Blueprint/UserWidget.h"
#include "SetInputModeCommand.generated.h"

UENUM()
enum class EInputMode : uint8
{
	GameAndUI,
	UI,
	Game
};

USTRUCT(BlueprintType)
struct FSetInputModeCommandData
{
	GENERATED_BODY()

	FSetInputModeCommandData(
		APlayerController* InPlayerController = nullptr,
		EInputMode InInputMode = EInputMode::GameAndUI,
		UUserWidget* InWidgetToFocus = nullptr,
		EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock,
		bool bInHideCursorDuringCapture = true
	)
	{
		PlayerController = InPlayerController;
		InputMode = InInputMode;
		WidgetToFocus = InWidgetToFocus;
		MouseLockMode = InMouseLockMode;
		bHideCursorDuringCapture = bInHideCursorDuringCapture;
	}

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set Input Mode Command")
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set Input Mode Command")
	EInputMode InputMode;

	/** Used for GameAndUI and UI */
	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set Input Mode Command")
	UUserWidget* WidgetToFocus;

	/** Used for GameAndUI and UI */
	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set Input Mode Command")
	EMouseLockMode MouseLockMode;

	/** Used for GameAndUI */
	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set Input Mode Command")
	bool bHideCursorDuringCapture;
};

/**
 * Command to set input mode
 */
UCLASS()
class COMMANDPACK_API USetInputModeCommand : public UBaseCommand
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Command Pack | Set Input Mode Command",
		meta = (WorldContext = "InWorldContextObject", CallableWithoutWorldContext)
	)
	bool Init(
		UPARAM(DisplayName="WorldContextObject") UObject* InWorldContextObject,
		UPARAM(DisplayName="Data") FSetInputModeCommandData InData
	);

	virtual void Execute_Implementation() override;

	UFUNCTION()
	void SetInputModeGameAndUI() const;

	UFUNCTION()
	void SetInputModeUIOnly() const;

	UFUNCTION()
	void SetInputModeGameOnly() const;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set Input Mode Command")
	FSetInputModeCommandData Data;
};
