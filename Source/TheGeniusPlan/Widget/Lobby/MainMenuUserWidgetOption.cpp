// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/Lobby/MainMenuUserWidgetOption.h"
#include "Components/Button.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"

void UMainMenuUserWidgetOption::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonGameStart)
	{
		ButtonGameStart->OnClicked.AddDynamic(this, &UMainMenuUserWidgetOption::ClickedGameStart);
	}
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &UMainMenuUserWidgetOption::ClickedOption);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UMainMenuUserWidgetOption::ClickedQuit);
	}

}

void UMainMenuUserWidgetOption::ClickedGameStart()
{
	if(EntryHUD)
	{
		EntryHUD->ShowWidget(WidgetType::LobbyWidget);
	}
}

void UMainMenuUserWidgetOption::ClickedOption()
{
	if(EntryHUD)
	{
		EntryHUD->ShowWidget(WidgetType::OptionWidget);
	}

}

void UMainMenuUserWidgetOption::ClickedQuit()
{
	if (EntryHUD)
	{
		EntryHUD->ShowWidget(WidgetType::LoginWidget);
	}
}
