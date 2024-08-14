// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEMultiplayerCourseGameMode.h"
#include "UEMultiplayerCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEMultiplayerCourseGameMode::AUEMultiplayerCourseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
