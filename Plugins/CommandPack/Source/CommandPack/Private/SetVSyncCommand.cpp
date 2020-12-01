// Gradess & Novaturion Company. All rights reserved.


#include "SetVSyncCommand.h"
#include "GameFramework/GameUserSettings.h"

bool USetVSyncCommand::Init_Implementation(
	UObject* InWorldContextObject,
	FSetVSyncCommandData InData
)
{
	const auto bResult = InitWorldContext(InWorldContextObject);

	Data = InData;
	
	return bResult;
}

void USetVSyncCommand::Execute_Implementation()
{
	auto GameUserSettings = UGameUserSettings::GetGameUserSettings();
	GameUserSettings->SetVSyncEnabled(Data.bEnable);
	GameUserSettings->ApplySettings(Data.bCheckCommandLineOverrides);
}
