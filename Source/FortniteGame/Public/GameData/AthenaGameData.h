// Copyright 1998-2023 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "Items/AthenaDanceItemDefinition.h"
#include "Items/AthenaPickaxeItemDefinition.h"
#include "Items/AthenaSeasonItemDefinition.h"
#include "Items/FortItemDefinition.h"
#include "Items/FortCosmeticItemMarkupTable.h"
#include "Items/AthenaBattleBusItemDefinition.h"
#include "Items/AthenaGliderItemDefinition.h"
#include "AthenaMusicPackItemDefinition.h"
#include "Customization/FortEmotePreviewActor.h"
#include "Customization/FortItemWrapPreviewActor.h"
#include "Customization/FortPickaxePreviewActor.h"
#include "Customization/FortLoadingScreenPreviewActor.h"
#include "Customization/FortMusicPackPreviewActor.h"
#include "Customization/FortSkyDiveContrailPreviewActor.h"
#include "Customization/FortSprayPreviewActor.h"
#include "Customization/FortBodyPartOverridePreviewActor.h"
#include "Weapons/Data/FortItemWrapMappingData.h"
#include "FortRespawnDataTable.h"
#include "FortniteGame.h"
#include "AthenaGameData.generated.h"

UCLASS()
class FORTNITEGAME_API UAthenaGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Fallback Cosmetics")
	TSoftObjectPtr<UAthenaPickaxeItemDefinition> FallbackPickaxe;

	UPROPERTY(EditAnywhere, Category = "Fallback Cosmetics")
	TSoftObjectPtr<UAthenaDanceItemDefinition> FallbackDance;

	UPROPERTY(EditAnywhere, Category = "Fallback Cosmetics")
	UAthenaSeasonItemDefinition* FallbackSeason;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TArray<TSoftObjectPtr<UFortItemDefinition>> ShuffleTileItemDefinitions;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UAthenaBattleBusItemDefinition* DefaultBattleBusSkin;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UAthenaGliderItemDefinition* DefaultGliderSkin;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UAthenaSkyDiveContrailItemDefinition* DefaultContrailEffect;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UAthenaMusicPackItemDefinition* DefaultMusicPack;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TArray<FPrimaryAssetId> ValidMaleSkinsForAnonymousMode;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TArray<FPrimaryAssetId> ValidFemaleSkinsForAnonymousMode;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TArray<FPrimaryAssetId> ValidBackPacksForAnonymousMode;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UFortCosmeticItemMarkupTable* CosmeticMarkupTable;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TSoftObjectPtr<UDataTable> CosmeticPreviewActionList;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortEmotePreviewActor> EmotePreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortItemWrapPreviewActor> ItemWrapPreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortLoadingScreenPreviewActor> LoadingScreenPreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortSprayPreviewActor> SprayPreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortMusicPackPreviewActor> MusicPackPreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortSkyDiveContrailPreviewActor> SkyDiveContrailPreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortBodyPartOverridePreviewActor> BodyPartOverridePreviewActorClass;

	UPROPERTY(EditAnywhere, Category = "Preview")
	TSoftClassPtr<AFortPickaxePreviewActor> PickaxeCosmeticPreviewActorClass;

//	UPROPERTY(EditAnywhere, Category = "Preview")
//	TMap<ECommonInputType, UTexture2D*> CosmeticPreviewActionMap;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UFortItemWrapMappingData* ItemWrapConfigAsset;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TSoftObjectPtr<UTexture2D> DeniedCosmeticThumbnail;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	UFortItemDefinition* PlaceholderItemToShowForDeniedCosmetics;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TArray<UAthenaCharacterItemDefinition*> RandomCharacters;

	UPROPERTY(EditAnywhere, Category = "Default Cosmetics")
	TArray<struct FGameplayTagMessage> UnableToPerformActionMessages;

	UPROPERTY(EditAnywhere, Category = "TOD")
	UCurveLinearColor* TimeOfDayRGBForPeripherals;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundMix* AthenaSoundMix;

	UPROPERTY(EditAnywhere, Category = "Sound")
	UReverbEffect* AthenaReverbEffect;

	UPROPERTY(EditAnywhere, Category = "Sound")
	FName AthenaReverbEffectTag;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundMix* VisualizationSoundMix;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraAnim* DroneCameraAnim;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraAnim* ThirdPersonCameraAnim;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraAnim* ArenaCameraAnim;

	//UPROPERTY(EditAnywhere, Category = "input")
	//TMap<ECommonInputType, UTexture2D*> InputTypeIcons;

	UPROPERTY(EditAnywhere, Category = "Respawn")
	UFortRespawnDataTable* RespawnDataTable;
	
};

