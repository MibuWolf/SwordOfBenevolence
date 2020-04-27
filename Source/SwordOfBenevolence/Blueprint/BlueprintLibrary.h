#pragma once
#include "CoreMinimal.h"
#include "BlueprintLibrary.generated.h"


UCLASS()
class UBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = DataTableConfig)
	static void LoadAllTableConfig();
};