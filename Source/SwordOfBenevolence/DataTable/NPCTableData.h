#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NPCTableData.generated.h"

USTRUCT()
struct FNPCTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32 LV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString AttributeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString Skills;

};