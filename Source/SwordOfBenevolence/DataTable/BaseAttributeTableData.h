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
	int32 MaxHp;		// Ѫ�����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MaxMp;		// ħ�������ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 ATK;			// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 DEF;			// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CRT;			// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 CHD;			// �����˺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MGK;			// ħ���˺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 RGS;			// ħ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCR;			// ħ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 MCD;			// ħ�������˺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 SPD;			// �ƶ��ٶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 EXP;			// �������辭��ֵ

};