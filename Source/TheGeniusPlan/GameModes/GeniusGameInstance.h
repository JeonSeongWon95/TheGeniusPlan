// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GeniusGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FPlayerScoreData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	int32 Score;
};
UCLASS()
class THEGENIUSPLAN_API UGeniusGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UGeniusGameInstance();

	UPROPERTY()
	ESelectedLand GI_SelectedLand;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	TArray<FPlayerScoreData> SavedPlayerScores;

	UPROPERTY()
	uint8 Number;

	UFUNCTION()
	void SetWinnerPlayer();

	UFUNCTION()
	void PrintWinnerPlayer();
};
