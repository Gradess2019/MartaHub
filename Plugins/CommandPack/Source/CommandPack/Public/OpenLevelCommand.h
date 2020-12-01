// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "OpenLevelCommand.generated.h"

USTRUCT(BlueprintType)
struct FOpenLevelCommandData
{
	GENERATED_BODY()

	FOpenLevelCommandData(
		const FName& InLevelName = NAME_None,
		bool bInAbsolute = true,
		const FString& InOptions = FString(TEXT(""))
	)
	{
		LevelName = InLevelName;
		bAbsolute = bInAbsolute;
		Options = InOptions;
	}

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Open Level Command")
	FName LevelName;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Open Level Command")
	bool bAbsolute;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Open Level Command")
	FString Options;
};

/**
 * Command to open level
 */
UCLASS()
class COMMANDPACK_API UOpenLevelCommand : public UBaseCommand
{
	GENERATED_BODY()

	static FString DefaultOptions;

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Command Pack | Open Level Command",
		meta=(WorldContext = "InWorldContextObject", CallableWithoutWorldContext)
	)
	bool Init(
		UPARAM(DisplayName="WorldContextObject") UObject* InWorldContextObject,
		UPARAM(DisplayName="Data") FOpenLevelCommandData InData
	);

	virtual void Execute_Implementation() override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Open Level Command")
	FOpenLevelCommandData Data;
};
