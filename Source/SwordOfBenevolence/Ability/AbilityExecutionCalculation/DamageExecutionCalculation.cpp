#include "DamageExecutionCalculation.h"
#include "../GameAbilitySystemComponent.h"
#include "../Attribute/ObjectAttribute.h"


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

	//计算物理伤害
	float AtkValue = FMath::Max<float>((Atk - Def), 0.0f);
	if (Crt > FMath::RandHelper(10000))
	{
		AtkValue += Atk * FMath::RandRange(0.5f, 1.5f);
	}

	//计算魔法伤害
	float MgkValue = FMath::Max<float>((Mgk - Rgs), 0.0f);
	if (Mcr > FMath::RandHelper(10000))
	{
		MgkValue += Mgk * FMath::RandRange(0.5f, 1.5f);
	}

	// 总伤害
	float Damage = AtkValue + MgkValue;
	HP -= Damage;
	HP = FMath::Max<float>(HP, 0.0f);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HPProperty, EGameplayModOp::Additive, HP));


}
