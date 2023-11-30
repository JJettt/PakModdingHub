// Copyright Epic Games, Inc. All Rights Reserved.

#include "Importers/MaterialParameterCollectionImporter.h"

#include "Dom/JsonObject.h"
#include "Materials/MaterialParameterCollection.h"
#include "Utilities/MathUtilities.h"

bool UMaterialParameterCollectionImporter::ImportData() {
	try {
		// Query properties for multi-use purposes
		TSharedPtr<FJsonObject> Properties = JsonObject->GetObjectField("Properties");

		UMaterialParameterCollection* MaterialParameterCollection = NewObject<UMaterialParameterCollection>(Cast<UObject>(Package), UMaterialParameterCollection::StaticClass(), *FileName, RF_Public | RF_Standalone);
		MaterialParameterCollection->StateId = CreateGUID(Properties->GetStringField("StateId"));

		const TArray<TSharedPtr<FJsonValue>>* ScalarParametersPtr;

		if (Properties->TryGetArrayField("ScalarParameters", ScalarParametersPtr)) {
			for (const TSharedPtr<FJsonValue> ScalarParameter : *ScalarParametersPtr) {
				TSharedPtr<FJsonObject> _ScalarParameter = ScalarParameter->AsObject();
				FCollectionScalarParameter ScalarParameter_Collection = FCollectionScalarParameter();

				ScalarParameter_Collection.DefaultValue = _ScalarParameter->GetNumberField("DefaultValue");
				ScalarParameter_Collection.ParameterName = FName(*_ScalarParameter->GetStringField("ParameterName"));
				ScalarParameter_Collection.Id = CreateGUID(_ScalarParameter->GetStringField("ID"));

				MaterialParameterCollection->ScalarParameters.Add(ScalarParameter_Collection);
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* VectorParametersPtr;

		if (Properties->TryGetArrayField("VectorParameters", VectorParametersPtr)) {
			for (const TSharedPtr<FJsonValue> VectorParameter : *VectorParametersPtr) {
				TSharedPtr<FJsonObject> _VectorParameter = VectorParameter->AsObject();
				FCollectionVectorParameter VectorParameter_Collection = FCollectionVectorParameter();

				VectorParameter_Collection.DefaultValue = FMathUtilities::ObjectToLinearColor(_VectorParameter->GetObjectField("DefaultValue").Get());
				VectorParameter_Collection.ParameterName = FName(*_VectorParameter->GetStringField("ParameterName"));
				VectorParameter_Collection.Id = CreateGUID(_VectorParameter->GetStringField("ID"));

				MaterialParameterCollection->VectorParameters.Add(VectorParameter_Collection);
			}
		}

		if (!HandleAssetCreation(MaterialParameterCollection)) return false;
	} catch (const char* Exception) {
		UE_LOG(LogJson, Error, TEXT("%s"), *FString(Exception));
		return false;
	}

	return true;
}
