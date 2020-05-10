#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UIViewTableData.generated.h"

USTRUCT()
struct FUIViewTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	int32	Layer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString	Path;

};