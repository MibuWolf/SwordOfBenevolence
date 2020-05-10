// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "../DataTable/AttributeTableData.h"
#include "../DataTable/CharacterLevelTableData.h"
#include "../DataTable/MonsterTableData.h"
#include "../DataTable/NPCTableData.h"
#include "../DataTable/SkillTableData.h"
#include "../DataTable/SkillAttributeTableData.h"
#include "SOBGameInstance.generated.h"

#define TABLEDATA_INTERFACE(TABLE_NAME)				\
F##TABLE_NAME##TableData*								Get##TABLE_NAME##TableData(FString Id)			\
{																										\
	FString TableName = #TABLE_NAME;																	\
	UDataTable** pDataTable = AllTableConfig.Find(TableName);											\
	if (pDataTable && *pDataTable) {																	\
		FString Contex;																					\
		F##TABLE_NAME##TableData* pData = (*pDataTable)->FindRow<F##TABLE_NAME##TableData>(FName(*Id), Contex);	\
		return pData;																			\
	}																									\
	return nullptr;																						\
}

UCLASS()
class SWORDOFBENEVOLENCE_API USOBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	// Constructor
	USOBGameInstance();

	// ���Ա�
	TABLEDATA_INTERFACE(Attribute);
	// ��ɫ�ȼ���
	TABLEDATA_INTERFACE(CharacterLevel);
	// �����
	TABLEDATA_INTERFACE(Monster);
	// NPC��
	TABLEDATA_INTERFACE(NPC);
	// Skill��
	TABLEDATA_INTERFACE(Skill);
	// Skill���Ա�
	TABLEDATA_INTERFACE(SkillAttribute);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTableConfig)
	TMap<FString, UDataTable*>			AllTableConfig;

};