// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/LobbyGameMode.h"

ALobbyGameMode::ALobbyGameMode()
{
	// DefaultPawnClass = ALobbyGameMode::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	// UE_LOG(LogTemp, Warning, TEXT("Logout!!"));
	Super::Logout(Exiting);
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	// UE_LOG(LogTemp, Warning, TEXT("PostLogin!!"));
	Super::PostLogin(NewPlayer);
}

