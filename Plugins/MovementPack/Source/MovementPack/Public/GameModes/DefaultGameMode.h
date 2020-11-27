// Gradess & Novaturion Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

/**
 * Default GameMode that is ready to go. Just put it in World Settings
 */
UCLASS()
class MOVEMENTPACK_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ADefaultGameMode(const FObjectInitializer& ObjectInitializer);
};
