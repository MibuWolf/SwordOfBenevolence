// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectAttribute.h"


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

		FMath::Clamp(NewValue, 0.0f, CurrentMaxMp);
	}
}

void UObjectAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
}

void UObjectAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
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
