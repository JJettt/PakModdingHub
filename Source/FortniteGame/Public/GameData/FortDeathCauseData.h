// Copyright 1998-2023 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GamePlayTags.h"
#include "FortDeathCauseData.generated.h"

USTRUCT()
struct FFortDeathCauseInfoVariant
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString DisplayText;

	UPROPERTY(EditAnywhere)
	FGameplayTag DeathCauseTag;

	UPROPERTY(EditAnywhere)
	TArray<FText> SelfInflictedMessages;

	UPROPERTY(EditAnywhere)
	TArray<FText> SelfInflictedDBNOMessages;

	UPROPERTY(EditAnywhere)
	TArray<FText> EliminatedMessages;

	UPROPERTY(EditAnywhere)
	TArray<FText> EliminatedDBNOMessages;
};

USTRUCT()
struct FFortDeathCauseInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	 FString DisplayText;

	UPROPERTY(EditAnywhere)
	 FGameplayTag DeathCauseTag;

	UPROPERTY(EditAnywhere)
	TArray<FText> SelfInflictedMessages;

	UPROPERTY(EditAnywhere)
	TArray<FText> SelfInflictedDBNOMessages;

	UPROPERTY(EditAnywhere)
	TArray<FText> EliminatedMessages;

	UPROPERTY(EditAnywhere)
	TArray<FText> EliminatedDBNOMessages;

	UPROPERTY(EditAnywhere)
	TArray<FFortDeathCauseInfoVariant> DeathCauseInfoVariants;
};


UCLASS()
class UFortDeathCauseData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Death Cause")
	TArray<FFortDeathCauseInfo> DeathCauseInfos; 
};
