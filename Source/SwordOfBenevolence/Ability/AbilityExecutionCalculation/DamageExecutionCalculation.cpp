#include "DamageExecutionCalculation.h"
#include "../GameAbilitySystemComponent.h"
#include "../Attribute/ObjectAttribute.h"
#include "../../GamePlay/SOBGameInstance.h"

// 声明要捕获的属性，并定义我们如何从“源”和“目标”中捕获它们。
struct SOBDamageStatics
{
	// HPDef目标HP
	DECLARE_ATTRIBUTE_CAPTUREDEF(HP);
	// DEFDef目标防御值
	DECLARE_ATTRIBUTE_CAPTUREDEF(DEF);
	// RGSDef目标魔法防御
	DECLARE_ATTRIBUTE_CAPTUREDEF(RGS);
	// ATKDef源攻击力
	DECLARE_ATTRIBUTE_CAPTUREDEF(ATK);
	// CRTDef源暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CRT);
	// MGKDef源魔法伤害
	DECLARE_ATTRIBUTE_CAPTUREDEF(MGK);
	// MCRDef源魔法暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(MCR);

	SOBDamageStatics()
	{
		// 目标HP
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, HP, Target, false);
		// 目标防御
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, DEF, Target, false);
		// 目标魔法防御
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, RGS, Target, false);

		// 源ATK
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, ATK, Source, false);
		// 源CRT暴击率
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, CRT, Source, false);
		// 源MGK魔法伤害
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, MGK, Source, false);
		// 源MCR魔法暴击率
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, MCR, Source, false);
	}
};

static const SOBDamageStatics& DamageStatics()
{
	static SOBDamageStatics DStatics;
	return DStatics;
}


UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().HPDef);
	RelevantAttributesToCapture.Add(DamageStatics().DEFDef);
	RelevantAttributesToCapture.Add(DamageStatics().RGSDef);
	RelevantAttributesToCapture.Add(DamageStatics().ATKDef);
	RelevantAttributesToCapture.Add(DamageStatics().CRTDef);
	RelevantAttributesToCapture.Add(DamageStatics().MGKDef);
	RelevantAttributesToCapture.Add(DamageStatics().MCRDef);
}


// 战斗计算公式  最终伤害  =  物理伤害   +   魔法伤害
// 物理伤害 = ( 攻击力 - 防御力 ) + random(技能攻击力提升下限， 技能攻击力提升上限) + （暴击率 + random(技能提升暴击率提升下限， 技能提升暴击率上限)）* 暴击值提升
// 魔法伤害 = ( 魔法攻击力 - 魔法防御力 ) + random(技能魔法攻击力提升下限， 技能魔法攻击力提升上限) + （魔法暴击率 + random(技能提升魔法暴击率提升下限， 技能魔法提升暴击率上限)）* 魔法暴击值提升
void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// 物理防御
	float Def = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, Def), 0.0f);
	// 魔法防御
	float Rgs = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().RGSDef, EvaluationParameters, Rgs), 0.0f);
	// 物理攻击
	float Atk = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ATKDef, EvaluationParameters, Atk), 0.0f);
	// 物理暴击
	float Crt = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CRTDef, EvaluationParameters, Crt), 0.0f);
	// 魔法伤害
	float Mgk = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MGKDef, EvaluationParameters, Mgk), 0.0f);
	// 魔法暴击率
	float Mcr = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MCRDef, EvaluationParameters, Mcr), 0.0f);
	// 血量
	float HP = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HPDef, EvaluationParameters, HP), 0.0f);

	float SkillATKMin = 0.0f, SkillATKMax = 0.0f, SkillCRTMin = 0.0f, SkillCRTMax = 0.0f, SkillCRTValue = 0.0f;
	float SkillMGKMin = 0.0f, SkillMGKMax = 0.0f, SkillMCRMin = 0.0f, SkillMCRMax = 0.0f, SkillMCRValue = 0.0f;

	const UGameAbility* pAbility = Cast<UGameAbility>(Spec.GetContext().GetAbility());
	if (pAbility != nullptr)
	{
		int32 skillID = pAbility->GetSkillID();
		int32 levelID = pAbility->GetSkillLevel();

		if (SourceActor)
		{
			UWorld* pWorld = SourceActor->GetWorld();
			if (pWorld)
			{
				USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

				if (pGameInstance)
				{
					FString strSkillID = FString::FromInt(skillID);
					FSkillTableData* pSkillTable = pGameInstance->GetSkillTableData(strSkillID);

					if (pSkillTable)
					{
						FString skillLevelID = pSkillTable->AttributeID + FString::FromInt(levelID);

						FSkillAttributeTableData* pSkillAttributeTable = pGameInstance->GetSkillAttributeTableData(skillLevelID);

						if (pSkillAttributeTable)
						{
							SkillATKMin = pSkillAttributeTable->ATKMin;			SkillATKMax = pSkillAttributeTable->ATKMax;		SkillCRTMin = pSkillAttributeTable->CRTMin;
							SkillCRTMax = pSkillAttributeTable->CRTMax;			SkillCRTValue = pSkillAttributeTable->CRTValue;

							SkillMGKMin = pSkillAttributeTable->MGKMin;			SkillMGKMax = pSkillAttributeTable->MGKMax;		SkillMCRMin = pSkillAttributeTable->MCRMin;
							SkillMCRMax = pSkillAttributeTable->MCRMax;			SkillMCRValue = pSkillAttributeTable->MCRValue;
						}
					}


				}
			}
		}
	}

	//计算物理伤害
	float AtkValue = FMath::Max<float>((Atk - Def), 0.0f);
	AtkValue += FMath::FRandRange(SkillATKMin, SkillATKMax);

	// 物理暴击率
	Crt += FMath::FRandRange(SkillCRTMin, SkillCRTMax);
	if (Crt > FMath::RandHelper(10000))
	{
		AtkValue += Atk * SkillCRTValue;
	}

	//计算魔法伤害
	float MgkValue = FMath::Max<float>((Mgk - Rgs), 0.0f);
	MgkValue += FMath::FRandRange(SkillMGKMin, SkillMGKMax);

	// 法术暴击率
	Mcr += FMath::FRandRange(SkillMCRMin, SkillMCRMax);
	if (Mcr > FMath::RandHelper(10000))
	{
		MgkValue += Mgk * SkillMCRValue;
	}

	// 总伤害
	int Damage = AtkValue + MgkValue;
	HP -= Damage;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HPProperty, EGameplayModOp::Additive, HP));

}
