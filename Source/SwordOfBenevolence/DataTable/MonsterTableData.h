#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterTableData.generated.h"

USTRUCT()
struct FMonsterTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString AttributeID;

};