#include "DamageExecutionCalculation.h"
#include "../GameAbilitySystemComponent.h"
#include "../Attribute/ObjectAttribute.h"


// ����Ҫ��������ԣ�������������δӡ�Դ���͡�Ŀ�ꡱ�в������ǡ�
struct SOBDamageStatics
{
	// HPDefĿ��HP
	DECLARE_ATTRIBUTE_CAPTUREDEF(HP);
	// DEFDefĿ�����ֵ
	DECLARE_ATTRIBUTE_CAPTUREDEF(DEF);
	// RGSDefĿ��ħ������
	DECLARE_ATTRIBUTE_CAPTUREDEF(RGS);
	// ATKDefԴ������
	DECLARE_ATTRIBUTE_CAPTUREDEF(ATK);
	// CRTDefԴ������
	DECLARE_ATTRIBUTE_CAPTUREDEF(CRT);
	// MGKDefԴħ���˺�
	DECLARE_ATTRIBUTE_CAPTUREDEF(MGK);
	// MCRDefԴħ��������
	DECLARE_ATTRIBUTE_CAPTUREDEF(MCR);

	SOBDamageStatics()
	{
		// Ŀ��HP
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, HP, Target, false);
		// Ŀ�����
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, DEF, Target, false);
		// Ŀ��ħ������
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, RGS, Target, false);

		// ԴATK
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, ATK, Source, false);
		// ԴCRT������
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, CRT, Source, false);
		// ԴMGKħ���˺�
		DEFINE_ATTRIBUTE_CAPTUREDEF(UObjectAttribute, MGK, Source, false);
		// ԴMCRħ��������
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

	// �������
	float Def = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, Def), 0.0f);
	// ħ������
	float Rgs = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().RGSDef, EvaluationParameters, Rgs), 0.0f);
	// ������
	float Atk = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ATKDef, EvaluationParameters, Atk), 0.0f);
	// ������
	float Crt = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CRTDef, EvaluationParameters, Crt), 0.0f);
	// ħ���˺�
	float Mgk = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MGKDef, EvaluationParameters, Mgk), 0.0f);
	// ħ��������
	float Mcr = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MCRDef, EvaluationParameters, Mcr), 0.0f);
	// Ѫ��
	float HP = FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HPDef, EvaluationParameters, HP), 0.0f);

	//���������˺�
	float AtkValue = FMath::Max<float>((Atk - Def), 0.0f);
	if (Crt > FMath::RandHelper(10000))
	{
		AtkValue += Atk * FMath::RandRange(0.5f, 1.5f);
	}

	//����ħ���˺�
	float MgkValue = FMath::Max<float>((Mgk - Rgs), 0.0f);
	if (Mcr > FMath::RandHelper(10000))
	{
		MgkValue += Mgk * FMath::RandRange(0.5f, 1.5f);
	}

	// ���˺�
	float Damage = AtkValue + MgkValue;
	HP -= Damage;
	HP = FMath::Max<float>(HP, 0.0f);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HPProperty, EGameplayModOp::Additive, HP));


}
