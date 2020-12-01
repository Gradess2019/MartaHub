// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "SetVSyncCommand.generated.h"

USTRUCT(BlueprintType)
struct FSetVSyncCommandData
{
	GENERATED_BODY()

	FSetVSyncCommandData(
		bool bInEnable = true,
		bool bInCheckCommandLineOverrides = true
	)
	{
		bEnable = bInEnable;
		bCheckCommandLineOverrides = bInCheckCommandLineOverrides;
	}

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set VSync Command")
	bool bEnable;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set VSync Command")
	bool bCheckCommandLineOverrides;
};

/**
 * Command to set VSync state
 */
UCLASS()
class COMMANDPACK_API USetVSyncCommand : public UBaseCommand
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Command Pack | Set VSync Command",
		meta=(WorldContext = "InWorldContextObject", CallableWithoutWorldContext)
	)
	bool Init(
		UPARAM(DisplayName="WorldContextObject") UObject* InWorldContextObject,
		UPARAM(DisplayName="Data") FSetVSyncCommandData InData
	);

	virtual void Execute_Implementation() override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Set VSync Command")
	FSetVSyncCommandData Data;
};
