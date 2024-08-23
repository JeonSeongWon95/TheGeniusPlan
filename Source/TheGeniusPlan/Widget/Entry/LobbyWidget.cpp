// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/Entry/LobbyWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Characters/EntryPawn.h"
#include "TheGeniusPlan/GameModes/Entry/EntryPlayerController.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(ButtonLeft)
	{
		ButtonLeft->OnClicked.AddDynamic(this, &ULobbyWidget::ChangeCharacterMesh);
	}
	if(ButtonRight)
	{
		ButtonRight->OnClicked.AddDynamic(this, &ULobbyWidget::ChangeCharacterMesh);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedQuit);
	}
	if (ButtonLogout)
	{
		ButtonLogout->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedLogout);
	}
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedOption);
	}
	if (ButtonServerJoin)
	{
		ButtonServerJoin->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedJoinServer);
	}
}

void ULobbyWidget::ChangeCharacterMesh()
{
	if (AEntryPlayerController* Controller = Cast<AEntryPlayerController>(EntryHUD->GetOwner()))
	{
		if(AEntryPawn* Pawn = Cast<AEntryPawn>(Controller->GetPawn()))
		{
			Pawn->ChangeMesh();
		}
	}
}

void ULobbyWidget::ClickedJoinServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Lobby")), true, FString(TEXT("127.0.0.1:7777")));
}

void ULobbyWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULobbyWidget::ClickedLogout()
{
	EntryHUD->ShowWidget(EntryWidgetType::LoginWidget);
}

void ULobbyWidget::ClickedOption()
{
	EntryHUD->ShowWidget(EntryWidgetType::OptionWidget);
}
