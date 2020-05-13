#include "PlayerAttribute.h"
#include "../../GamePlay/SOBGameInstance.h"

#define CONVERSIONRATE	10.0f	

UPlayerAttribute::UPlayerAttribute()
{

}

// ������ҵȼ���ʼ������
void	UPlayerAttribute::InitializeByPlayerLevel(int32 Level)
{
	UWorld* pWorld = GetWorld();
	if (!pWorld)
		return;

	USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

	if (pGameInstance == nullptr)
		return;

	FString characterLevel = FString::FromInt(Level);
	FCharacterLevelTableData* pCharacterLevel = pGameInstance->GetCharacterLevelTableData(characterLevel);
	if (pCharacterLevel == nullptr)
		return;

	FGameAttributeTableData* GameAttribute = pGameInstance->GetGameAttributeTableData(pCharacterLevel->GameAttribute);
	if (GameAttribute == nullptr)
		return;

	STR = GameAttribute->STR;	// ���� Ӱ�칥����
	VIT = GameAttribute->VIT;	// ���� Ӱ�������
	TEN = GameAttribute->TEN;	// ���� Ӱ�����Ѫ��
	AGI = GameAttribute->AGI;	// ���� Ӱ����������
	WIS = GameAttribute->WIS;	// ���� Ӱ�취���˺�
	SPT = GameAttribute->SPT;	// ��־ Ӱ�����ħ��ֵ
	CTN = GameAttribute->CTN;	// ���� Ӱ�취������
	WIL = GameAttribute->WIL;	// רע Ӱ�취��������

	FBaseAttributeTableData* BaseAttribute = pGameInstance->GetBaseAttributeTableData(pCharacterLevel->BaseAttribute);
	if (BaseAttribute == nullptr)
		return;

	MaxHp = HP = BaseAttribute->MaxHp + float(GameAttribute->STR) / CONVERSIONRATE;
	MaxMp = MP = BaseAttribute->MaxMp + float(GameAttribute->SPT) / CONVERSIONRATE;
	ATK = BaseAttribute->ATK + float(GameAttribute->STR) / CONVERSIONRATE;
	DEF = BaseAttribute->DEF + float(GameAttribute->VIT) / CONVERSIONRATE;
	CRT = BaseAttribute->CRT + float(GameAttribute->AGI) / CONVERSIONRATE;
	CHD = BaseAttribute->CHD;
	MGK = BaseAttribute->MGK + float(GameAttribute->WIS) / CONVERSIONRATE;
	RGS = BaseAttribute->RGS + float(GameAttribute->CTN) / CONVERSIONRATE;
	MCR = BaseAttribute->MCR + float(GameAttribute->WIL) / CONVERSIONRATE;
	MCD = BaseAttribute->MCD;
	SPD = BaseAttribute->SPD;

	if (EXP.GetBaseValue() >= MAXEXP.GetBaseValue())
	{
		EXP.SetBaseValue(FMath::Min(EXP.GetBaseValue() - MAXEXP.GetBaseValue(), 0.0f));
		EXP.SetCurrentValue(FMath::Min(EXP.GetBaseValue() - MAXEXP.GetBaseValue(), 0.0f));
	}
	
	MAXEXP = BaseAttribute->EXP;
}


void UPlayerAttribute::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
}

void UPlayerAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
}

void UPlayerAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}
