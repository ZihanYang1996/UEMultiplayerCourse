// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEMultiplayerCourseGameMode.h"
#include "UEMultiplayerCourseCharacter.h"
#include "Kismet/GameplayStatics.h"
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

void AUEMultiplayerCourseGameMode::HostLANGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Hosting LAN Game"));
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonExampleMap?listen");
}

void AUEMultiplayerCourseGameMode::JoinLANGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining LAN Game"));
	APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
	if (PC)
	{
		PC->ClientTravel("192.168.2.66", TRAVEL_Absolute);
	}
}