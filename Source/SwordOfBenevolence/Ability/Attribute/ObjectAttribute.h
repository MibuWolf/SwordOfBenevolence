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
	// Invalid	无效的
	Invalid			UMETA(DisplayName = "Invalid"),
	// HP		当前血量
	HP				UMETA(DisplayName = "HP"),
	// MaxHp	最大血量
	MaxHp			UMETA(DisplayName = "MaxHp"),
	// MP		当前魔法
	MP				UMETA(DisplayName = "MP"),
	// MaxMp	最大魔法
	MaxMp			UMETA(DisplayName = "MaxMp"),
	// ATK		攻击力(物理)
	ATK				UMETA(DisplayName = "ATK"),
	// DEF		防御力(物理)
	DEF				UMETA(DisplayName = "DEF"),
	// CRT		暴击(物理)
	CRT				UMETA(DisplayName = "CRT"),
	// STR		力量(影响物理攻击力数值)
	STR				UMETA(DisplayName = "STR"),
	// VIT		耐力(影响物理防御力数值)
	VIT				UMETA(DisplayName = "VIT"),
	// TEN		韧性(影响最大血量)
	TEN				UMETA(DisplayName = "TEN"),
	// AGI		敏捷(影响物理暴击率数值)
	AGI				UMETA(DisplayName = "AGI"),
	// MGK		魔法伤害
	MGK				UMETA(DisplayName = "MGK"),
	// RGS		魔法防御
	RGS				UMETA(DisplayName = "RGS"),
	// WIS		智力(影响魔法伤害)
	WIS				UMETA(DisplayName = "WIS"),
	// SPT		精神(影响魔法防御)
	SPT				UMETA(DisplayName = "SPT"),
	// CTN		专注力(影响魔法暴击率)
	CTN				UMETA(DisplayName = "CTN"),
	// SPD		移动速度
	SPD				UMETA(DisplayName = "SPD"),
	// CON		体质（影响玩家负重）
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

	/** 暴击(物理暴击) */
	UPROPERTY(BlueprintReadOnly, Category = "CRT")
	FGameplayAttributeData CRT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CRT)

	/** 力量(影响物理攻击力数值) */
	UPROPERTY(BlueprintReadOnly, Category = "STR")
	FGameplayAttributeData STR;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, STR)

	/** 耐力(影响物理防御力数值) */
	UPROPERTY(BlueprintReadOnly, Category = "VIT")
	FGameplayAttributeData VIT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, VIT)

	/** 韧性(影响最大血量) */
	UPROPERTY(BlueprintReadOnly, Category = "TEN")
	FGameplayAttributeData TEN;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, TEN)

	/** 敏捷(影响物理暴击率) */
	UPROPERTY(BlueprintReadOnly, Category = "AGI")
	FGameplayAttributeData AGI;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, AGI)

	/** 魔法伤害 */
	UPROPERTY(BlueprintReadOnly, Category = "MGK")
	FGameplayAttributeData MGK;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MGK)

	/** 魔法防御 */
	UPROPERTY(BlueprintReadOnly, Category = "RGS")
	FGameplayAttributeData RGS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, RGS)

	/** 智力(影响魔法伤害) */
	UPROPERTY(BlueprintReadOnly, Category = "WIS")
	FGameplayAttributeData WIS;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, WIS)

	/** 精神(影响魔法防御) */
	UPROPERTY(BlueprintReadOnly, Category = "SPT")
	FGameplayAttributeData SPT;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, SPT)

	/** 专注力(影响魔法暴击率) */
	UPROPERTY(BlueprintReadOnly, Category = "CTN")
	FGameplayAttributeData CTN;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CTN)

	/** 移动速度 */
	UPROPERTY(BlueprintReadOnly, Category = "SPD")
	FGameplayAttributeData SPD;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, SPD)

	/** 体质（影响玩家负重） */
	UPROPERTY(BlueprintReadOnly, Category = "CON")
	FGameplayAttributeData CON;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CON)

	/** 当前经验值 */
	UPROPERTY(BlueprintReadOnly, Category = "CUREXP")
	FGameplayAttributeData CUREXP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, CUREXP)

	/** 当前升级需要的经验值 */
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
