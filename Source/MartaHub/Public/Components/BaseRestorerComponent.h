// Gradess Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Restorer.h"
#include "BaseRestorerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable)
class MARTAHUB_API UBaseRestorerComponent : public UActorComponent, public IRestorer
{
	GENERATED_BODY()

public:
	UBaseRestorerComponent();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Restorer")
	UCurveFloat* Lerp;
};
