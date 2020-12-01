// Gradess & Novaturion Company. All rights reserved.


#include "QuitCommand.h"
#include "Kismet/KismetSystemLibrary.h"

bool UQuitCommand::Init_Implementation(
	UObject* InWorldContextObject,
	FQuitCommandData InData
)
{
	const bool bResult = InitWorldContext(InWorldContextObject);
	
	Data = InData;
	
	return bResult;
}

void UQuitCommand::Execute_Implementation()
{
	UKismetSystemLibrary::QuitGame(
		WorldContextObject,
		Data.PlayerController,
		Data.QuitPreference,
		Data.bIgnorePlatformRestrictions
	);
}
