// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "../HUD/UIManager.h"
#include "../DataTable/BaseAttributeTableData.h"
#include "../DataTable/GameAttributeTableData.h"
#include "../DataTable/CharacterLevelTableData.h"
#include "../DataTable/MonsterTableData.h"
#include "../DataTable/NPCTableData.h"
#include "../DataTable/SkillTableData.h"
#include "../DataTable/UIViewTableData.h"
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

	virtual void Init();

public:

	// Constructor
	USOBGameInstance();

	// �������Ա�
	TABLEDATA_INTERFACE(BaseAttribute);
	// ��Ϸ���Ա�(��������)
	TABLEDATA_INTERFACE(GameAttribute);
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
	// UI���ñ�
	TABLEDATA_INTERFACE(UIView);

public:

	// ����UI��ʾ
	UFUNCTION(BlueprintCallable, Category = UI)
	void	ShowUIView(FString ViewName);

	// ����UI����
	UFUNCTION(BlueprintCallable, Category = UI)
	void	HideUIView(FString ViewName);

	// ����UI����
	UFUNCTION(BlueprintCallable, Category = UI)
	void	DestoryUIView(FString ViewName);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTableConfig)
	TMap<FString, UDataTable*>			AllTableConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GamePlayerController)
	TSubclassOf<UUIManager>	UIViewManager;	// UI������

	UUIManager*				pUIViewManager = nullptr;
};