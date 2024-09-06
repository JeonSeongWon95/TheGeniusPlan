// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFPlayerController.h"



#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/AAFSelectWidget.h"
#include "TheGeniusPlan/Widget/MainGame/ShowPlayerSeletedLandWidget.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"
#include "TheGeniusPlan/Widget/TimerWidget.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Actor/AAFLandLoction.h"



AAAFPlayerController::AAAFPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CSWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/WG_AAFStart.WG_AAFStart_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CEWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/WG_AAFGameEnd.WG_AAFGameEnd_C'"));


	if (CSWidget.Succeeded())
	{
		GameStartWidgetClass = CSWidget.Class;
	}
	if (CEWidget.Succeeded())
	{
		GameEndWidgetClass = CEWidget.Class;
	}

	//UPROPERTY()
	//TObjectPtr<class UUserWidget> GameStartWidget;

	//UPROPERTY()
	//TObjectPtr<class UUserWidget> GameEndWidget;

}

void AAAFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	BindDispatcher();

	check(GameStartWidgetClass);
	check(GameEndWidgetClass);

	if (GameStartWidget == nullptr)
	{
		GameStartWidget = CreateWidget<UUserWidget>(GetWorld(), GameStartWidgetClass);
		GameStartWidget->AddToViewport();
	}
	else
	{
		if (GameStartWidget->IsInViewport())
		{

		}
		else
		{
			GameStartWidget->AddToViewport();
		}
	}

	if (GameEndWidget == nullptr)
	{
		GameEndWidget = CreateWidget<UUserWidget>(GetWorld(), GameEndWidgetClass);
	}
}

void AAAFPlayerController::GameStepChange(EGameStep NewStep)
{
	UE_LOG(LogTemp, Error, TEXT("New Step : %d"), NewStep);

	if (GameState)
	{
		switch (NewStep)
		{
		case EGameStep::SetLocation:
			RequestGameStateFunction();
			break;

		case EGameStep::RoundStart:

			if(GameStartWidget->IsInViewport())
			{
				GameStartWidget->RemoveFromParent();
			}
			MoveActor();
			break;

		case EGameStep::RoundEnd:

			if (!GameEndWidget->IsInViewport())
			{
				GameEndWidget->AddToViewport();
			}

		default:
			break;
		}
	}


}

void AAAFPlayerController::BindDispatcher()
{
	if (PlayerState != nullptr)
	{
		CastPlayerState = Cast<AAAFPlayerState>(PlayerState);

		if (GameState)
		{
			if (!GameState->EventDisptacherGameStepChange.IsBound())
			{
				GameState->EventDisptacherGameStepChange.AddDynamic(this, &AAAFPlayerController::GameStepChange);
				UE_LOG(LogTemp, Error, TEXT("Bind Success"));
			}

			GetWorld()->GetTimerManager().ClearTimer(TimerHandletwo);
			return;
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(TimerHandletwo, this, &AAAFPlayerController::BindDispatcher, 0.1f, false);
}

void AAAFPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AAAFPlayerController::MoveActor()
{
	Server_MoveActor();
}

void AAAFPlayerController::RequestGameStateFunction()
{
	ResponseGameStateFunction();
}

void AAAFPlayerController::ResponseGameStateFunction_Implementation()
{
	GameState->RequestGameStepReset();
}

void AAAFPlayerController::Client_MoveActor_Implementation()
{
	APawn* thisPawn = GetPawn();

	if (thisPawn)
	{
		if (CastPlayerState)
		{
			FVector NewLocation = CastPlayerState->Location;
			thisPawn->SetActorLocation(NewLocation);
			UE_LOG(LogTemp, Error, TEXT("ActorMove : %f, %f, %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
		}
	}

}

void AAAFPlayerController::Server_MoveActor_Implementation()
{
	Client_MoveActor();

	if(HasAuthority())
	{
		APawn* thisPawn = GetPawn();

		if (thisPawn)
		{
			if (CastPlayerState)
			{
				FVector NewLocation = CastPlayerState->Location;
				thisPawn->SetActorLocation(NewLocation);
				UE_LOG(LogTemp, Error, TEXT("ActorMove : %f, %f, %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
			}
		}
	}
}


