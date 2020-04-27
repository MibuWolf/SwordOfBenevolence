#include "DataTableConfig.h"
#include "AttributeTableData.h"

void	UDataTableConfig::LoadAllConfig()
{

	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/DataConfig/Attribute.Attribute'"));

}
