// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectAttribute.h"
#include "GameplayEffectExtension.h"

UObjectAttribute::UObjectAttribute()
	: HP(100.0f)
	, MaxHp(100.0f)
	, MP(100.0f)
	, MaxMp(100.0f)
{

}

void UObjectAttribute::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if (Attribute == GetMPAttribute())
	{

		const float CurrentCurrentValue = MP.GetCurrentValue();
		const float CurrentMaxMp = MaxMp.GetCurrentValue();

		NewValue = FMath::Clamp(NewValue, 0.0f, CurrentMaxMp);
	}

	if (Attribute == GetHPAttribute())
	{

		const float CurrentCurrentHP = HP.GetCurrentValue();
		const float CurrentMaxHp = MaxHp.GetCurrentValue();

		NewValue = FMath::Clamp(NewValue, 0.0f, CurrentMaxHp);
	}
}

void UObjectAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(), 0.0f, GetMaxHp()));
	}

	if (Data.EvaluatedData.Attribute == GetMPAttribute())
	{
		SetMP(FMath::Clamp(GetMP(), 0.0f, GetMaxMp()));
	}
}

void UObjectAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

}


void UObjectAttribute::InitializeAttribute(FBaseAttributeTableData* BaseAttribute)
{
	if (BaseAttribute == nullptr)
		return;

	MaxHp = HP = BaseAttribute->MaxHp;
	MaxMp = MP = BaseAttribute->MaxMp;
	ATK = BaseAttribute->ATK;
	DEF = BaseAttribute->DEF;
	CRT = BaseAttribute->CRT;
	CHD = BaseAttribute->CHD;
	MGK = BaseAttribute->MGK;
	RGS = BaseAttribute->RGS;
	MCR = BaseAttribute->MCR;
	MCD = BaseAttribute->MCD;
	SPD = BaseAttribute->SPD;
}

//void UObjectAttribute::OnRep_HP()
//{
//}
//
//void UObjectAttribute::OnRep_MaxHP()
//{
//}
//
//void UObjectAttribute::OnRep_MP()
//{
//}
//
//void UObjectAttribute::OnRep_MaxMP()
//{
//}
