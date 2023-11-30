#include "AthenaDanceItemDefinition.h"
#include "Editor/EditorEngine.h"
#include "EditorFramework/AssetImportData.h"

UAthenaDanceItemDefinition::UAthenaDanceItemDefinition()
{
	ItemType = EFortItemType::AthenaDance;
	GameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Cosmetics.EmoteType.Dance")));
}