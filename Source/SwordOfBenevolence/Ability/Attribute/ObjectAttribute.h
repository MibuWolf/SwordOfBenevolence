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


// 属性定义
// 如果需要服务器改变属性回调 则要这样定义  UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_##AttributeName)		
#define ATTRIBUTE_DEFINE(AttributeName)		\
UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute")		\
FGameplayAttributeData AttributeName;																	\
ATTRIBUTE_ACCESSORS(UObjectAttribute, AttributeName)


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
	ATTRIBUTE_DEFINE(HP)

	/** 最大血量 */
	ATTRIBUTE_DEFINE(MaxHp)

	/** 当前蓝量 */
	ATTRIBUTE_DEFINE(MP)

	/** 最大蓝量 */
	ATTRIBUTE_DEFINE(MaxMp)

	/** 物理攻击力 */
	ATTRIBUTE_DEFINE(ATK)

	/** 物理防御力 */
	ATTRIBUTE_DEFINE(DEF)

	/** 暴击(物理暴击) */
	ATTRIBUTE_DEFINE(CRT)

	/** 力量(影响物理攻击力数值) */
	ATTRIBUTE_DEFINE(STR)

	/** 耐力(影响物理防御力数值) */
	ATTRIBUTE_DEFINE(VIT)

	/** 韧性(影响最大血量) */
	ATTRIBUTE_DEFINE(TEN)

	/** 敏捷(影响物理暴击率) */
	ATTRIBUTE_DEFINE(AGI)
	
	/** 魔法伤害 */
	ATTRIBUTE_DEFINE(MGK)

	/** 魔法防御 */
	ATTRIBUTE_DEFINE(RGS)

	/** 智力(影响魔法伤害) */
	ATTRIBUTE_DEFINE(WIS)

	/** 精神(影响魔法防御) */
	ATTRIBUTE_DEFINE(SPT)

	/** 专注力(影响魔法暴击率) */
	ATTRIBUTE_DEFINE(CTN)

	/** 移动速度 */
	ATTRIBUTE_DEFINE(SPD)

	/** 体质（影响玩家负重） */
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
