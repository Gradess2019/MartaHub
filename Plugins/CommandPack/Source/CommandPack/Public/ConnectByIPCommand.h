// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "ConnectByIPCommand.generated.h"

USTRUCT(BlueprintType)
struct FConnectByIPCommandData
{
	GENERATED_BODY()

	FConnectByIPCommandData(
		const FString& InIP = FString(TEXT("127.0.0.1")),
		APlayerController* InPlayerController = nullptr
	)
	{
		IP = InIP;
		PlayerController = InPlayerController;
	}

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Connect By IP Command")
	FString IP;

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Connect By IP Command")
	APlayerController* PlayerController;
};

/**
 * Command to connect by ip
 */
UCLASS()
class COMMANDPACK_API UConnectByIPCommand : public UBaseCommand
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		BlueprintNativeEvent,
		Category = "Command Pack | Connect By IP Command",
		meta=(WorldContext = "InWorldContextObject", CallableWithoutWorldContext)
	)
	bool Init(
		UPARAM(DisplayName="WorldContextObject") UObject* InWorldContextObject,
		UPARAM(DisplayName="Data") FConnectByIPCommandData InData
	);

	virtual void Execute_Implementation() override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Command Pack | Connect By IP Command")
	FConnectByIPCommandData Data;
};
