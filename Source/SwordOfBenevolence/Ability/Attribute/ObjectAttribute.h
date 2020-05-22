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

	/** 当前血量 */
	UPROPERTY(BlueprintReadOnly, Category = "HP")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, HP)

	/** 最大血量 */
	UPROPERTY(BlueprintReadOnly, Category = "MaxHp")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MaxHp)

	/** 当前蓝量 */
	UPROPERTY(BlueprintReadOnly, Category = "MP")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MP)

	/** 最大蓝量 */
	UPROPERTY(BlueprintReadOnly, Category = "MaxMp")
	FGameplayAttributeData MaxMp;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MaxMp)
	
	/** 物理攻击力 */
	UPROPERTY(BlueprintReadOnly, Category = "ATK")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, ATK)

	/** 物理防御力 */
	UPROPERTY(BlueprintReadOnly, Category = "DEF")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, DEF)

	/** 暴击率(物理暴击) */
	UPROPERTY(BlueprintReadOnly, Category = "CRT")
	FGameplayAttributeData CRT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CRT)

	/** 暴击伤害 */
	UPROPERTY(BlueprintReadOnly, Category = "CHD")
	FGameplayAttributeData CHD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CHD)

	/** 魔法伤害 */
	UPROPERTY(BlueprintReadOnly, Category = "MGK")
	FGameplayAttributeData MGK;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MGK)

	/** 魔法防御 */
	UPROPERTY(BlueprintReadOnly, Category = "RGS")
	FGameplayAttributeData RGS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, RGS)

	/** 魔法暴击率 */
	UPROPERTY(BlueprintReadOnly, Category = "MCR")
	FGameplayAttributeData MCR;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MCR)

	/** 魔法暴击伤害 */
	UPROPERTY(BlueprintReadOnly, Category = "MCD")
	FGameplayAttributeData MCD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MCD)

	/** 移动速度 */
	UPROPERTY(BlueprintReadOnly, Category = "SPD")
	FGameplayAttributeData SPD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, SPD)

	/** 攻击速度 */
	UPROPERTY(BlueprintReadOnly, Category = "ATS")
	FGameplayAttributeData ATS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, ATS)

	/** 当前经验值 */
	UPROPERTY(BlueprintReadOnly, Category = "EXP")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, EXP)

	/** 当前升级需要的经验值 */
	UPROPERTY(BlueprintReadOnly, Category = "MAXEXP")
	FGameplayAttributeData MAXEXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MAXEXP)


public:

// 根据怪物ID初始化属性
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
