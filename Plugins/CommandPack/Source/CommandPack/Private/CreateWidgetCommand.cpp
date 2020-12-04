// Gradess & Novaturion Company. All rights reserved.


#include "CreateWidgetCommand.h"
#include "SetInputModeCommand.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

bool UCreateWidgetCommand::Init_Implementation(
	UObject* InWorldContextObject,
	FCreateWidgetCommandData InData
)
{
	const auto bResult = InitWorldContext(InWorldContextObject);

	if (!IsValid(InData.Owner))
	{
		InData.Owner = UGameplayStatics::GetPlayerController(InWorldContextObject, 0);
	}

	Data = InData;

	return bResult;
}

UUserWidget* UCreateWidgetCommand::GetWidget_Implementation(bool& bSuccess)
{
	bSuccess = IsValid(Widget);
	return Widget;
}

void UCreateWidgetCommand::Execute_Implementation()
{
	if (!IsValid(Data.UserWidgetClass)) { return; }

	Widget = CreateWidget(Data.Owner, Data.UserWidgetClass, Data.WidgetName);
	if (!IsValid(Widget)) { return; }

	if (Data.bAddToViewport)
	{
		Widget->AddToViewport(Data.ZOrder);
	}
	
	if (Data.bUIMode)
	{
		auto SetInputModeCommand = NewObject<USetInputModeCommand>(this, USetInputModeCommand::StaticClass());
		const auto InputCommandData = FSetInputModeCommandData(this->Data.Owner, EInputMode::UI, Widget);
		SetInputModeCommand->Init(WorldContextObject, InputCommandData);
		SetInputModeCommand->Execute();
	}
	
	Data.Owner->bShowMouseCursor = Data.bShowMouseCursor;
}
