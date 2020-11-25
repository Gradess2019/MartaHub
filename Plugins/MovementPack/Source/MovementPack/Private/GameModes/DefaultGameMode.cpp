// Gradess & Novaturion Company. All rights reserved.


#include "GameModes/DefaultGameMode.h"
#include "DefaultPlayerController.h"
#include "Actors/Characters/DefaultPlayerCharacter.h"

ADefaultGameMode::ADefaultGameMode(const FObjectInitializer& ObjectInitializer)
	: AGameModeBase(ObjectInitializer)
{
	DefaultPawnClass = ADefaultPlayerCharacter::StaticClass();
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	DefaultPlayerName = FText::FromString(TEXT("Unknown member"));
}
