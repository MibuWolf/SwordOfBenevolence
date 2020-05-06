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
	FString Name;				// ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString SkillIcon;			// ����Icon

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString SkillInfo;			// ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString SkillBlueprint;		// ������ͼ

};