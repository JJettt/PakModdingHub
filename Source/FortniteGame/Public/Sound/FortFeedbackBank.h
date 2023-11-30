// Copyright 1998-2023 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FortniteGame.h"
#include "FortFeedbackBank.generated.h"

class UFortFeedbackBank;

USTRUCT(BlueprintType)
struct FFortFeedbackHandle
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	 UFortFeedbackBank* FeedbackBank;

	UPROPERTY(EditAnywhere)
	 FName EventName;

	UPROPERTY(EditAnywhere)
	bool ReadOnly;

	UPROPERTY(EditAnywhere)
	bool bBankDefined;

	UPROPERTY(EditAnywhere)
	EFortFeedbackBroadcastFilter BroadcastFilterOverride;                         
};

USTRUCT()
struct FFortFeedbackResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FFortFeedbackHandle Handle;
	
	UPROPERTY(EditAnywhere)
	EFortFeedbackContext Context;                                           
};

USTRUCT()
struct FFortFeedbackLine
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> Audio;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UAnimSequence> AnimSequence;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UAnimMontage> AnimMontage;

	UPROPERTY(EditAnywhere)
	EFortFeedbackAddressee Addressee;

	UPROPERTY(EditAnywhere)
	EFortFeedbackContext Context;

	UPROPERTY(EditAnywhere)
	TArray<FFortFeedbackResponse> ResponseEvents;

	UPROPERTY(EditAnywhere)
	bool bInterruptCurrentLine;

	UPROPERTY(EditAnywhere)
	bool bCanBeInterrupted;

	UPROPERTY(EditAnywhere)
	bool bCanQue;
};

USTRUCT()
struct FFortFeedbackAction
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	 FFortFeedbackHandle Handle;

	UPROPERTY(EditAnywhere)
	TArray<FFortFeedbackLine> Lines;                                            
};

USTRUCT()
struct FFortFeedbackActionBankDefined : public FFortFeedbackAction
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	float MinReplayTime;
	
	UPROPERTY(EditAnywhere)
	float inReplayTimeForSpeaker;
};

UCLASS()
class UFortFeedbackBank : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Feedback")
	TArray<FFortFeedbackActionBankDefined> BankDefinedFeedbackEvents;
protected:
	UPROPERTY(EditAnywhere, Category = "Feedback")
	TArray<FFortFeedbackAction> FeedbackEvents;
};
