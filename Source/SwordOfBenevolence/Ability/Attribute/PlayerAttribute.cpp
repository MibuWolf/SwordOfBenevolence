#include "PlayerAttribute.h"
#include "../../GamePlay/SOBGameInstance.h"

#define CONVERSIONRATE	10.0f	

UPlayerAttribute::UPlayerAttribute()
{

}

// 根据玩家等级初始化属性
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

	STR = GameAttribute->STR;	// 力量 影响攻击力
	VIT = GameAttribute->VIT;	// 耐力 影响防御力
	TEN = GameAttribute->TEN;	// 韧性 影响最大血量
	AGI = GameAttribute->AGI;	// 敏捷 影响物理暴击率
	WIS = GameAttribute->WIS;	// 智力 影响法术伤害
	SPT = GameAttribute->SPT;	// 意志 影响最大魔法值
	CTN = GameAttribute->CTN;	// 精神 影响法术防御
	WIL = GameAttribute->WIL;	// 专注 影响法术暴击率

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
