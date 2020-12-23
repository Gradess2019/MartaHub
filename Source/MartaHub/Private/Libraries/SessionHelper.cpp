// Gradess Games. All rights reserved.

#include "Libraries/SessionHelper.h"
#include "AdvancedSessionsLibrary.h"
#include "Kismet/GameplayStatics.h"

bool USessionHelper::IsSession(UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) { return false; }
	
	const auto PlayerIndex = 0;
	const auto PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex);
	
	auto NetId = FBPUniqueNetId();
	UAdvancedSessionsLibrary::GetUniqueNetID(PlayerController, NetId);

	
	//
	// auto bInSession = false;
	// UAdvancedSessionsLibrary::IsPlayerInSession(WorldContextObject, NetId, bInSession);
	// return bInSession;
	return true;
}
