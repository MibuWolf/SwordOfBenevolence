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
	UPROPERTY(BlueprintReadOnly, Category = "HP")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, HP)

	/** ���Ѫ�� */
	UPROPERTY(BlueprintReadOnly, Category = "MaxHp")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MaxHp)

	/** ��ǰ���� */
	UPROPERTY(BlueprintReadOnly, Category = "MP")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MP)

	/** ������� */
	UPROPERTY(BlueprintReadOnly, Category = "MaxMp")
	FGameplayAttributeData MaxMp;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MaxMp)
	
	/** �������� */
	UPROPERTY(BlueprintReadOnly, Category = "ATK")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, ATK)

	/** ��������� */
	UPROPERTY(BlueprintReadOnly, Category = "DEF")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, DEF)

	/** ����(������) */
	UPROPERTY(BlueprintReadOnly, Category = "CRT")
	FGameplayAttributeData CRT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CRT)

	/** ����(Ӱ������������ֵ) */
	UPROPERTY(BlueprintReadOnly, Category = "STR")
	FGameplayAttributeData STR;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, STR)

	/** ����(Ӱ�������������ֵ) */
	UPROPERTY(BlueprintReadOnly, Category = "VIT")
	FGameplayAttributeData VIT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, VIT)

	/** ����(Ӱ�����Ѫ��) */
	UPROPERTY(BlueprintReadOnly, Category = "TEN")
	FGameplayAttributeData TEN;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, TEN)

	/** ����(Ӱ����������) */
	UPROPERTY(BlueprintReadOnly, Category = "AGI")
	FGameplayAttributeData AGI;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, AGI)

	/** ħ���˺� */
	UPROPERTY(BlueprintReadOnly, Category = "MGK")
	FGameplayAttributeData MGK;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MGK)

	/** ħ������ */
	UPROPERTY(BlueprintReadOnly, Category = "RGS")
	FGameplayAttributeData RGS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, RGS)

	/** ����(Ӱ��ħ���˺�) */
	UPROPERTY(BlueprintReadOnly, Category = "WIS")
	FGameplayAttributeData WIS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, WIS)

	/** ����(Ӱ��ħ������) */
	UPROPERTY(BlueprintReadOnly, Category = "SPT")
	FGameplayAttributeData SPT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, SPT)

	/** רע��(Ӱ��ħ��������) */
	UPROPERTY(BlueprintReadOnly, Category = "CTN")
	FGameplayAttributeData CTN;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CTN)

	/** �ƶ��ٶ� */
	UPROPERTY(BlueprintReadOnly, Category = "SPD")
	FGameplayAttributeData SPD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, SPD)

	/** ���ʣ�Ӱ����Ҹ��أ� */
	UPROPERTY(BlueprintReadOnly, Category = "CON")
	FGameplayAttributeData CON;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CON)

	/** ��ǰ����ֵ */
	UPROPERTY(BlueprintReadOnly, Category = "CUREXP")
	FGameplayAttributeData CUREXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CUREXP)

	/** ��ǰ������Ҫ�ľ���ֵ */
	UPROPERTY(BlueprintReadOnly, Category = "EXP")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, EXP)

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
