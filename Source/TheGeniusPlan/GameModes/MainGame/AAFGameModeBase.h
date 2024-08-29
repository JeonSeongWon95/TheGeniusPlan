// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
#include "AAFGameModeBase.generated.h"

UCLASS()
class THEGENIUSPLAN_API AAAFGameModeBase : public AMainGameModeBase
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<class AAAFGameState> CastGameState;

	UFUNCTION()
	void TravelLevel();

	AAAFGameModeBase();

	UFUNCTION()
	void BindGameState();

	UFUNCTION()
	void GameStepChange(EGameStep NewStep);

	FTimerHandle GameModeTimerHandle;

	UFUNCTION()
	void ChangeEndGame();

	FTimerHandle GameModeSecondHandle;
};

