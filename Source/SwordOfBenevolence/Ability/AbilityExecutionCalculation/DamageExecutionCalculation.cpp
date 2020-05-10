#include "DamageExecutionCalculation.h"
#include "../GameAbilitySystemComponent.h"
#include "../Attribute/ObjectAttribute.h"
#include "../../GamePlay/SOBGameInstance.h"

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


// ս�����㹫ʽ  �����˺�  =  �����˺�   +   ħ���˺�
// �����˺� = ( ������ - ������ ) + random(���ܹ������������ޣ� ���ܹ�������������) + �������� + random(���������������������ޣ� ������������������)��* ����ֵ����
// ħ���˺� = ( ħ�������� - ħ�������� ) + random(����ħ���������������ޣ� ����ħ����������������) + ��ħ�������� + random(��������ħ���������������ޣ� ����ħ����������������)��* ħ������ֵ����
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

	//���������˺�
	float AtkValue = FMath::Max<float>((Atk - Def), 0.0f);
	AtkValue += FMath::FRandRange(SkillATKMin, SkillATKMax);

	// ��������
	Crt += FMath::FRandRange(SkillCRTMin, SkillCRTMax);
	if (Crt > FMath::RandHelper(10000))
	{
		AtkValue += Atk * SkillCRTValue;
	}

	//����ħ���˺�
	float MgkValue = FMath::Max<float>((Mgk - Rgs), 0.0f);
	MgkValue += FMath::FRandRange(SkillMGKMin, SkillMGKMax);

	// ����������
	Mcr += FMath::FRandRange(SkillMCRMin, SkillMCRMax);
	if (Mcr > FMath::RandHelper(10000))
	{
		MgkValue += Mgk * SkillMCRValue;
	}

	// ���˺�
	int Damage = AtkValue + MgkValue;
	HP -= Damage;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HPProperty, EGameplayModOp::Additive, HP));

}
