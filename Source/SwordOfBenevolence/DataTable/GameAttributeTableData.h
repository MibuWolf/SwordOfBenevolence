#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameAttributeTableData.generated.h"

USTRUCT()
struct FGameAttributeTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 STR;			// 力量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 VIT;			// 耐力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 TEN;			// 韧性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 AGI;			// 敏捷
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 WIS;			// 智力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 SPT;			// 精神
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 CTN;			// 专注
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 WIL;			// 意志

};