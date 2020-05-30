#include "GameMonster.h"
#include "../../GamePlay/SOBGameInstance.h"
#include "../../Ability/Attribute/ObjectAttribute.h"

AGameMonster::AGameMonster()
	:Super()
{
	Attribute = CreateDefaultSubobject<UObjectAttribute>(TEXT("ObjectAttribute"));
}

void AGameMonster::BeginPlay()
{
	Super::BeginPlay();

	InitMonsterAttribute();
}

void AGameMonster::InitMonsterAttribute()
{
	if (Attribute)
	{
		UWorld* pWorld = GetWorld();
		if (!pWorld)
			return;

		USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

		if (pGameInstance == nullptr)
			return;

		FMonsterTableData* pMonsterData = pGameInstance->GetMonsterTableData(MonsterID);
		if (pMonsterData == nullptr)
			return;

		FBaseAttributeTableData* BaseAttribute = pGameInstance->GetBaseAttributeTableData(pMonsterData->AttributeID);

		if (BaseAttribute != nullptr)
			Attribute->InitializeAttribute(BaseAttribute);
	}
}

void AGameMonster::OnDelayDestory()
{
	Destroy();
}

void AGameMonster::OnDeath()
{
	UWorld* World = GetWorld();

	if (World == nullptr)
		return;

	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, this, &AGameMonster::OnDelayDestory, 3.0f, false);
}
