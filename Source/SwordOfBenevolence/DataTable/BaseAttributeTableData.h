#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BaseAttributeTableData.generated.h"

USTRUCT()
struct FBaseAttributeTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MaxHp;		// 血量最大值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MaxMp;		// 魔法量最大值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 ATK;			// 攻击力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 DEF;			// 防御力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CRT;			// 暴击率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CHD;			// 暴击伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MGK;			// 魔法伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 RGS;			// 魔法防御
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCR;			// 魔法暴击率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCD;			// 魔法暴击伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 SPD;			// 移动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 EXP;			// 升级所需经验值

};