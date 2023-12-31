﻿// Copyright 1998-2023 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "FortTimeOfDayManager.h"
#include "FortTimeOfDayCollection.h"
#include "FortniteGame.h"
#include "GamePlayTags.h"
#include "FortTimeOfDayData.generated.h"

USTRUCT(BlueprintType)
struct FFortTimeOfDayTheme {
	GENERATED_BODY()
public:
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	TArray<UFortTimeOfDayCollection*> TimeOfDayCollections;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	TArray<TSoftClassPtr<AFortTimeOfDayManager>> AdditionalTimeOfDayManagers;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	TArray<TSoftClassPtr<AFortTimeOfDayManager>> ProhibitedTimeOfDayManagers;
    
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
	TArray<TSoftClassPtr<AFortTimeOfDayManager>> ValidTimeOfDayManagers;
};

USTRUCT(BlueprintType)
struct FFortWindIntensityAndDirection
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	float WindIntensity;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	float WindHeading;
};

USTRUCT(BlueprintType)
struct FFortGlobalWindInfo {
	GENERATED_BODY()
public:
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	TArray<FFortWindIntensityAndDirection> ValidWindInfos;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
	int32 WindIndex;
};

USTRUCT()
struct FORTNITEGAME_API FWorldAmbientPropertiesMatchingGameContext
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FGameplayTagQuery QueryToMatch;

	UPROPERTY(EditAnywhere)
	FFortTimeOfDayTheme TimeOfDayTheme;                         

	UPROPERTY(EditAnywhere)
	FFortGlobalWindInfo GlobalWindInfo;                                
};

UCLASS()
class FORTNITEGAME_API UFortTimeOfDayData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "World Ambient Properties")
	TArray<FWorldAmbientPropertiesMatchingGameContext> WorldAmbientPropertiesList;
};

