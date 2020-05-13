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
		int32 STR;			// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 VIT;			// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 TEN;			// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 AGI;			// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 WIS;			// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 SPT;			// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 CTN;			// רע
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
		int32 WIL;			// ��־

};