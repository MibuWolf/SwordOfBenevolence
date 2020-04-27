#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTableConfig.generated.h"


UCLASS()
class UDataTableConfig : public UObject
{
	GENERATED_BODY()

public:

	static UDataTableConfig*			GetInstance()
	{
		static UDataTableConfig instance;

		return &instance;
	}

	void		LoadAllConfig();

private:

};
