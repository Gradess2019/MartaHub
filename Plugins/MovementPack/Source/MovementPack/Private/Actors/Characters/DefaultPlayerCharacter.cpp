// Gradess & Novaturion Company. All rights reserved.

#include "Actors/Characters/DefaultPlayerCharacter.h"

void ADefaultPlayerCharacter::AddForward_Implementation(const float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ADefaultPlayerCharacter::AddRight_Implementation(const float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ADefaultPlayerCharacter::AddUp_Implementation(const float AxisValue)
{
	AddMovementInput(GetActorUpVector(), AxisValue);
}

void ADefaultPlayerCharacter::AddTurnAround_Implementation(const float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ADefaultPlayerCharacter::AddLookUp_Implementation(const float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ADefaultPlayerCharacter::Space_Implementation()
{
	Jump();
}
