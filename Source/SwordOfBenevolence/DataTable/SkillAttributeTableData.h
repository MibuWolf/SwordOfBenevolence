#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillAttributeTableData.generated.h"

USTRUCT()
struct FSkillAttributeTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 ATKMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 ATKMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CRTMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CRTMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CRTValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MGKMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MGKMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCRMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCRMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCRValue;

};