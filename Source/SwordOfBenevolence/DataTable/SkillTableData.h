#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillTableData.generated.h"

USTRUCT()
struct FSkillTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString Name;				// 技能名称

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString SkillIcon;			// 技能Icon

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString SkillInfo;			// 技能描述

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString SkillBlueprint;		// 技能蓝图

};