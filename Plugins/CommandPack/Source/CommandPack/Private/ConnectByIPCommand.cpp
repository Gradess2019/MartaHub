// Gradess & Novaturion Company. All rights reserved.


#include "ConnectByIPCommand.h"
#include "Kismet/KismetSystemLibrary.h"

bool UConnectByIPCommand::Init_Implementation(
	UObject* InWorldContextObject,
	FConnectByIPCommandData InData
)
{
	const auto bResult = InitWorldContext(InWorldContextObject);

	Data = InData;

	return bResult;
}

void UConnectByIPCommand::Execute_Implementation()
{
	const auto Command = FString(TEXT("open ")).Append(Data.IP);
	UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, Command, Data.PlayerController);
}
