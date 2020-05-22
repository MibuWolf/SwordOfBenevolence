// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeType.h"
#include "../../DataTable/BaseAttributeTableData.h"
#include "ObjectAttribute.generated.h"


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

	/** ������(������) */
	UPROPERTY(BlueprintReadOnly, Category = "CRT")
	FGameplayAttributeData CRT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CRT)

	/** �����˺� */
	UPROPERTY(BlueprintReadOnly, Category = "CHD")
	FGameplayAttributeData CHD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CHD)

	/** ħ���˺� */
	UPROPERTY(BlueprintReadOnly, Category = "MGK")
	FGameplayAttributeData MGK;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MGK)

	/** ħ������ */
	UPROPERTY(BlueprintReadOnly, Category = "RGS")
	FGameplayAttributeData RGS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, RGS)

	/** ħ�������� */
	UPROPERTY(BlueprintReadOnly, Category = "MCR")
	FGameplayAttributeData MCR;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MCR)

	/** ħ�������˺� */
	UPROPERTY(BlueprintReadOnly, Category = "MCD")
	FGameplayAttributeData MCD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MCD)

	/** �ƶ��ٶ� */
	UPROPERTY(BlueprintReadOnly, Category = "SPD")
	FGameplayAttributeData SPD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, SPD)

	/** �����ٶ� */
	UPROPERTY(BlueprintReadOnly, Category = "ATS")
	FGameplayAttributeData ATS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, ATS)

	/** ��ǰ����ֵ */
	UPROPERTY(BlueprintReadOnly, Category = "EXP")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, EXP)

	/** ��ǰ������Ҫ�ľ���ֵ */
	UPROPERTY(BlueprintReadOnly, Category = "MAXEXP")
	FGameplayAttributeData MAXEXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MAXEXP)


public:

// ���ݹ���ID��ʼ������
void	InitializeAttribute(FBaseAttributeTableData* BaseAttribute);

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
