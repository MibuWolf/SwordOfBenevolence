#include "BlueprintLibrary.h"
#include "../DataTable/DataTableConfig.h"


UBlueprintLibrary::UBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void	UBlueprintLibrary::LoadAllTableConfig()
{
	UDataTableConfig::GetInstance()->LoadAllConfig();
}