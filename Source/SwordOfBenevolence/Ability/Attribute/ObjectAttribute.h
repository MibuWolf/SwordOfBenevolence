// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ObjectAttribute.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


// ���Զ���
// �����Ҫ�������ı����Իص� ��Ҫ��������  UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_##AttributeName)		
#define ATTRIBUTE_DEFINE(AttributeName)		\
UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute")		\
FGameplayAttributeData AttributeName;																	\
ATTRIBUTE_ACCESSORS(UObjectAttribute, AttributeName)


UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	// Invalid	��Ч��
	Invalid			UMETA(DisplayName = "Invalid"),
	// HP		��ǰѪ��
	HP				UMETA(DisplayName = "HP"),
	// MaxHp	���Ѫ��
	MaxHp			UMETA(DisplayName = "MaxHp"),
	// MP		��ǰħ��
	MP				UMETA(DisplayName = "MP"),
	// MaxMp	���ħ��
	MaxMp			UMETA(DisplayName = "MaxMp"),
	// ATK		������(����)
	ATK				UMETA(DisplayName = "ATK"),
	// DEF		������(����)
	DEF				UMETA(DisplayName = "DEF"),
	// CRT		����(����)
	CRT				UMETA(DisplayName = "CRT"),
	// STR		����(Ӱ������������ֵ)
	STR				UMETA(DisplayName = "STR"),
	// VIT		����(Ӱ�������������ֵ)
	VIT				UMETA(DisplayName = "VIT"),
	// TEN		����(Ӱ�����Ѫ��)
	TEN				UMETA(DisplayName = "TEN"),
	// AGI		����(Ӱ������������ֵ)
	AGI				UMETA(DisplayName = "AGI"),
	// MGK		ħ���˺�
	MGK				UMETA(DisplayName = "MGK"),
	// RGS		ħ������
	RGS				UMETA(DisplayName = "RGS"),
	// WIS		����(Ӱ��ħ���˺�)
	WIS				UMETA(DisplayName = "WIS"),
	// SPT		����(Ӱ��ħ������)
	SPT				UMETA(DisplayName = "SPT"),
	// CTN		רע��(Ӱ��ħ��������)
	CTN				UMETA(DisplayName = "CTN"),
	// SPD		�ƶ��ٶ�
	SPD				UMETA(DisplayName = "SPD"),
	// CON		���ʣ�Ӱ����Ҹ��أ�
	CON				UMETA(DisplayName = "CON"),
};

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UObjectAttribute : public UAttributeSet
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	UObjectAttribute();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	/** ��ǰѪ�� */
	ATTRIBUTE_DEFINE(HP)

	/** ���Ѫ�� */
	ATTRIBUTE_DEFINE(MaxHp)

	/** ��ǰ���� */
	ATTRIBUTE_DEFINE(MP)

	/** ������� */
	ATTRIBUTE_DEFINE(MaxMp)

	/** �������� */
	ATTRIBUTE_DEFINE(ATK)

	/** ��������� */
	ATTRIBUTE_DEFINE(DEF)

	/** ����(������) */
	ATTRIBUTE_DEFINE(CRT)

	/** ����(Ӱ������������ֵ) */
	ATTRIBUTE_DEFINE(STR)

	/** ����(Ӱ�������������ֵ) */
	ATTRIBUTE_DEFINE(VIT)

	/** ����(Ӱ�����Ѫ��) */
	ATTRIBUTE_DEFINE(TEN)

	/** ����(Ӱ����������) */
	ATTRIBUTE_DEFINE(AGI)
	
	/** ħ���˺� */
	ATTRIBUTE_DEFINE(MGK)

	/** ħ������ */
	ATTRIBUTE_DEFINE(RGS)

	/** ����(Ӱ��ħ���˺�) */
	ATTRIBUTE_DEFINE(WIS)

	/** ����(Ӱ��ħ������) */
	ATTRIBUTE_DEFINE(SPT)

	/** רע��(Ӱ��ħ��������) */
	ATTRIBUTE_DEFINE(CTN)

	/** �ƶ��ٶ� */
	ATTRIBUTE_DEFINE(SPD)

	/** ���ʣ�Ӱ����Ҹ��أ� */
	ATTRIBUTE_DEFINE(CON)

protected:

	/*UFUNCTION()
	virtual void OnRep_HP();

	UFUNCTION()
	virtual void OnRep_MaxHP();

	UFUNCTION()
	virtual void OnRep_MP();

	UFUNCTION()
	virtual void OnRep_MaxMP();*/


};
