#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterLevelTableData.generated.h"

USTRUCT()
struct FCharacterLevelTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString BaseAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeTableData)
	FString GameAttribute;

};