#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeType.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	// INVALID	无效的
	INVALID			UMETA(DisplayName = "INVALID"),
	// STR		力量
	STR				UMETA(DisplayName = "STR"),
	// VIT		耐力
	VIT				UMETA(DisplayName = "VIT"),
	// TEN		韧性
	TEN				UMETA(DisplayName = "TEN"),
	// AGI		敏捷
	AGI				UMETA(DisplayName = "AGI"),
	// WIS		智力
	WIS				UMETA(DisplayName = "WIS"),
	// WIL 		意志
	WIL 			UMETA(DisplayName = "WIL"),
	// SPT		精神
	SPT				UMETA(DisplayName = "SPT"),
	// CTN		专注
	CTN				UMETA(DisplayName = "CTN"),

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
	// CHD		暴击伤害(物理)
	CHD				UMETA(DisplayName = "CHD"),
	// MGK		魔法伤害
	MGK				UMETA(DisplayName = "MGK"),
	// MCR		魔法暴击率
	MCR				UMETA(DisplayName = "MCR"),
	// RGS		魔法防御
	RGS				UMETA(DisplayName = "RGS"),
	// MCD		魔法暴击伤害
	MCD				UMETA(DisplayName = "MCD"),
	// ATS		攻击速度
	ATS				UMETA(DisplayName = "ATS"),
	// SPD		移动速度
	SPD				UMETA(DisplayName = "SPD"),
	// EXP		经验（当前经验值）
	EXP				UMETA(DisplayName = "EXP"),
	// CON		升级经验（升级所需要的经验值）
	MAXEXP			UMETA(DisplayName = "MAXEXP"),
};
