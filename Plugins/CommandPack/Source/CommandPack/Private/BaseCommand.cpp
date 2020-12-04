// Gradess & Novaturion Company. All rights reserved.


#include "BaseCommand.h"

bool UBaseCommand::InitWorldContext_Implementation(UObject* InWorldContextObject)
{
	WorldContextObject = InWorldContextObject;
	return IsValid(WorldContextObject);
}

void UBaseCommand::Execute_Implementation()
{
	unimplemented();
}
