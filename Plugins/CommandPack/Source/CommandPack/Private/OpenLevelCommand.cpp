// Gradess & Novaturion Company. All rights reserved.


#include "OpenLevelCommand.h"
#include "Kismet/GameplayStatics.h"

bool UOpenLevelCommand::Init_Implementation(
	UObject* InWorldContextObject,
	FOpenLevelCommandData InData
)
{
	const bool bResult = InitWorldContext(InWorldContextObject);

	Data = InData;

	return bResult;
}

void UOpenLevelCommand::Execute_Implementation()
{
	UGameplayStatics::OpenLevel(WorldContextObject, Data.LevelName, Data.bAbsolute, Data.Options);
}
