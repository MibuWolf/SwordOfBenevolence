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

	// 基础属性表
	TABLEDATA_INTERFACE(BaseAttribute);
	// 游戏属性表(二级属性)
	TABLEDATA_INTERFACE(GameAttribute);
	// 角色等级表
	TABLEDATA_INTERFACE(CharacterLevel);
	// 怪物表
	TABLEDATA_INTERFACE(Monster);
	// NPC表
	TABLEDATA_INTERFACE(NPC);
	// Skill表
	TABLEDATA_INTERFACE(Skill);
	// Skill属性表
	TABLEDATA_INTERFACE(SkillAttribute);
	// UI配置表
	TABLEDATA_INTERFACE(UIView);

public:

	// 控制UI显示
	UFUNCTION(BlueprintCallable, Category = UI)
	void	ShowUIView(FString ViewName);

	// 控制UI隐藏
	UFUNCTION(BlueprintCallable, Category = UI)
	void	HideUIView(FString ViewName);

	// 控制UI销毁
	UFUNCTION(BlueprintCallable, Category = UI)
	void	DestoryUIView(FString ViewName);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTableConfig)
	TMap<FString, UDataTable*>			AllTableConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GamePlayerController)
	TSubclassOf<UUIManager>	UIViewManager;	// UI管理器

	UUIManager*				pUIViewManager = nullptr;
};