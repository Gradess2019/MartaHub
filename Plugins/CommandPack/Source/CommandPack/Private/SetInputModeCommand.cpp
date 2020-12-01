// Gradess & Novaturion Company. All rights reserved.


#include "SetInputModeCommand.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

bool USetInputModeCommand::Init_Implementation(UObject* InWorldContextObject, FSetInputModeCommandData InData)
{
	const auto bResult = InitWorldContext(InWorldContextObject);

	if (IsValid(InData.PlayerController))
	{
		InData.PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	}

	Data = InData;

	return bResult;
}

void USetInputModeCommand::Execute_Implementation()
{
	switch (Data.InputMode)
	{
	case EInputMode::GameAndUI:
		{
			SetInputModeGameAndUI();
			break;
		}

	case EInputMode::UI:
		{
			SetInputModeUIOnly();
			break;
		}

	case EInputMode::Game:
		{
			SetInputModeGameOnly();
			break;
		}
	}
}

void USetInputModeCommand::SetInputModeGameAndUI() const
{
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
		Data.PlayerController,
		Data.WidgetToFocus,
		Data.MouseLockMode,
		Data.bHideCursorDuringCapture
	);
}

void USetInputModeCommand::SetInputModeUIOnly() const
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(
		Data.PlayerController,
		Data.WidgetToFocus,
		Data.MouseLockMode
	);
}

void USetInputModeCommand::SetInputModeGameOnly() const
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(
		Data.PlayerController
	);
}
