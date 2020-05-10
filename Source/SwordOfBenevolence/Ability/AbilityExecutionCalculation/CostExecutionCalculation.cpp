#include "CostExecutionCalculation.h"
#include "../GameAbilitySystemComponent.h"
#include "../Attribute/ObjectAttribute.h"
#include "../GameAbility/GameAbility.h"
#include "../../DataTable/SkillTableData.h"
#include "../../DataTable/SkillAttributeTableData.h"
#include "../../GamePlay/SOBGameInstance.h"


UCostExecutionCalculation::UCostExecutionCalculation()
{
	RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(FGameplayAttribute(FindFieldChecked<UProperty>(UObjectAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(UObjectAttribute, MP)))
		, EGameplayEffectAttributeCaptureSource::Source, false));
}


float UCostExecutionCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec & Spec) const
{
	const UGameAbility* pAbility = Cast<UGameAbility>(Spec.GetContext().GetAbility());

	if (!pAbility)
		return 0.0f;

	int32 skillID = pAbility->GetSkillID();
	int32 levelID = pAbility->GetSkillLevel();

	AActor* SourceActor = Cast<AActor>(Spec.GetContext().GetSourceObject());

	if (!SourceActor)
		return 0.0f;

	UWorld* pWorld = SourceActor->GetWorld();
	if (!pWorld)
		return 0.0f;

	USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

	if (!pGameInstance)
		return 0.0f;

	FString strSkillID = FString::FromInt(skillID);
	FSkillTableData* pSkillTable = pGameInstance->GetSkillTableData(strSkillID);

	if (!pSkillTable)
		return 0.0f;

	FString skillLevelID = pSkillTable->AttributeID + FString::FromInt(levelID);

	FSkillAttributeTableData* pSkillAttributeTable = pGameInstance->GetSkillAttributeTableData(skillLevelID);

	if (!pSkillAttributeTable)
		return 0.0f;

	// MP
	float CostMp = pSkillAttributeTable->MP;

	return -CostMp;
}
