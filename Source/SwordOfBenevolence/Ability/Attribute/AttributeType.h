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
	// INVALID	��Ч��
	INVALID			UMETA(DisplayName = "INVALID"),
	// STR		����
	STR				UMETA(DisplayName = "STR"),
	// VIT		����
	VIT				UMETA(DisplayName = "VIT"),
	// TEN		����
	TEN				UMETA(DisplayName = "TEN"),
	// AGI		����
	AGI				UMETA(DisplayName = "AGI"),
	// WIS		����
	WIS				UMETA(DisplayName = "WIS"),
	// WIL 		��־
	WIL 			UMETA(DisplayName = "WIL"),
	// SPT		����
	SPT				UMETA(DisplayName = "SPT"),
	// CTN		רע
	CTN				UMETA(DisplayName = "CTN"),

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
	// CHD		�����˺�(����)
	CHD				UMETA(DisplayName = "CHD"),
	// MGK		ħ���˺�
	MGK				UMETA(DisplayName = "MGK"),
	// MCR		ħ��������
	MCR				UMETA(DisplayName = "MCR"),
	// RGS		ħ������
	RGS				UMETA(DisplayName = "RGS"),
	// MCD		ħ�������˺�
	MCD				UMETA(DisplayName = "MCD"),
	// ATS		�����ٶ�
	ATS				UMETA(DisplayName = "ATS"),
	// SPD		�ƶ��ٶ�
	SPD				UMETA(DisplayName = "SPD"),
	// EXP		���飨��ǰ����ֵ��
	EXP				UMETA(DisplayName = "EXP"),
	// CON		�������飨��������Ҫ�ľ���ֵ��
	MAXEXP			UMETA(DisplayName = "MAXEXP"),
};
