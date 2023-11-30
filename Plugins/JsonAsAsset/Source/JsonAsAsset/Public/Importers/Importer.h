﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Utilities/ObjectUtilities.h"
#include "Utilities/PropertyUtilities.h"
#include "Widgets/Notifications/SNotificationList.h"

// Global handler for converting JSON to assets
class IImporter {
public:
	IImporter() {
	}

	IImporter(const FString& FileName, const FString& FilePath, const TSharedPtr<FJsonObject>& JsonObject, UPackage* Package, UPackage* OutermostPkg, const TArray<TSharedPtr<FJsonValue>>& AllJsonObjects = {}) {
		this->FileName = FileName;
		this->FilePath = FilePath;
		this->JsonObject = JsonObject;
		this->Package = Package;
		this->OutermostPkg = OutermostPkg;
		this->AllJsonObjects = AllJsonObjects;
		this->PropertySerializer = NewObject<UPropertySerializer>();
		this->GObjectSerializer = NewObject<UObjectSerializer>();
		this->GObjectSerializer->SetPropertySerializer(PropertySerializer);
	}

	virtual ~IImporter() {
	}

	// Import the data of the supported type, return if successful or not
	virtual bool ImportData() { return false; }

protected:
	UPROPERTY()
		UPropertySerializer* PropertySerializer;
private:
	UPROPERTY()
	UObjectSerializer* GObjectSerializer;

	TArray<FString> AcceptedTypes = {
		"CurveTable",
		"CurveFloat",
		"CurveVector",
		"CurveLinearColor",
		"CurveLinearColorAtlas",
		"Skeleton",
		"AnimSequence",
		"AnimMontage",
		"Material",
		"MaterialFunction",
		"MaterialInstanceConstant",
		"MaterialParameterCollection",
		"DataTable",
		"LandscapeGrassType",
		"ReverbEffect",
		"SoundAttenuation",
		"SoundConcurrency",
		"SubsurfaceProfile",
		"PhysicalMaterial"
	};

public:
	template <class T = UObject>
	// Loads a reference to a object	
	void LoadObject(const TSharedPtr<FJsonObject>* PackageIndex, T*& Object);
	template <class T = UObject>
	// Loads a array of references
	TArray<T*> LoadObject(const TArray<TSharedPtr<FJsonValue>>& PackageArray, TArray<T*> Array);

	// Refers to AcceptedTypes to see if type is valid ------------------
	bool CanImport(const FString& ImporterType) { return AcceptedTypes.Contains(ImporterType); }

	FGuid CreateGUID(FString String) {
		FGuid GUID;
		FGuid::Parse(String, GUID);

		return GUID;
	}

	bool CanImportAny(TArray<FString>& Types) {
		for (FString& Type : Types) {
			if (!CanImport(Type)) continue;
			return true;
		}

		return false;
	}

	TArray<FString> GetAcceptedTypes() { return AcceptedTypes; }
	// ------------------------------------------------------------------------

	void ImportReference(const FString& File);
	bool HandleReference(const FString& GamePath);

	bool HandleExports(TArray<TSharedPtr<FJsonValue>> Exports, FString File, bool bHideNotifications = false);

	/*
	* Gets a reference from AllJsonObjects
	* 
	* Example (PackageIndex):
	* {
          "ObjectName": "Class'Asset:ExportName'",
          "ObjectPath": "/Game/Asset.Index"
    * }
	*/
	TSharedPtr<FJsonObject> GetExport(FJsonObject* PackageIndex);

	// Easier way to add notifications to Editor
	virtual void AppendNotification(const FText& Text, const FText& SubText, float ExpireDuration, SNotificationItem::ECompletionState CompletionState, bool bUseSuccessFailIcons = false, float WidthOverride = 500);
	virtual void AppendNotification(const FText& Text, const FText& SubText, float ExpireDuration, const FSlateBrush* SlateBrush, SNotificationItem::ECompletionState CompletionState, bool bUseSuccessFailIcons = false, float WidthOverride = 500);

protected:
	bool HandleAssetCreation(UObject* Asset) const;
	void SavePackage();

	// Wrapper for remote downloading
	template <class T = UObject>
	T* DownloadWrapper(T* InObject, FString Type, FString Name, FString Path);

	FName GetExportNameOfSubobject(const FString& PackageIndex);
	TArray<TSharedPtr<FJsonValue>> FilterExportsByOuter(const FString& Outer);
	TSharedPtr<FJsonValue> GetExportByObjectPath(const TSharedPtr<FJsonObject>& Object);

	FORCEINLINE UObjectSerializer* GetObjectSerializer() const { return GObjectSerializer; }
	FString FileName;
	FString FilePath;
	TSharedPtr<FJsonObject> JsonObject;
	UPackage* Package;
	UPackage* OutermostPkg;

	TArray<TSharedPtr<FJsonValue>> AllJsonObjects;
};
