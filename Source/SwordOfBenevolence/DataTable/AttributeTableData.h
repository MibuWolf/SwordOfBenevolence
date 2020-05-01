#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AttributeTableData.generated.h"

USTRUCT()
struct FAttributeTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MaxMp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 ATK;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 DEF;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CRT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 STR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 VIT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 TEN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 AGI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MGK;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 RGS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 WIS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 SPT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CTN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 SPD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CON;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 EXP;

};