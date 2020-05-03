#include "HeadHPBarWidgetBase.h"
#include "../GameObject/GameObject.h"
#include "../Ability/Attribute/ObjectAttribute.h"

void UHeadHPBarWidgetBase::Initialization(AGameObject* pOwner)
{
	Owner = pOwner;

	if (Owner == nullptr)
		return;

	UAbilitySystemComponent* pAbilityComponent = pOwner->GetAbilitySystemComponent();
	UObjectAttribute* pAttribute = pOwner->GetAttribute();
	if (pAbilityComponent == nullptr || pAttribute == nullptr)
		return;

	// Attribute change callbacks
	HPEventHandle = pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetHPAttribute()).AddUObject(this, &UHeadHPBarWidgetBase::OnHPChanged);
	MaxHPEventHandle = pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetMaxHpAttribute()).AddUObject(this, &UHeadHPBarWidgetBase::OnMaxHPChanged);
	MPEventHandle = pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetMPAttribute()).AddUObject(this, &UHeadHPBarWidgetBase::OnMPChanged);
	MaxMPEventHandle = pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetMaxMpAttribute()).AddUObject(this, &UHeadHPBarWidgetBase::OnMaxMPChanged);

	SetLevel(Owner->GetLevel());
	SetName(Owner->GetName());
}


void UHeadHPBarWidgetBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Owner == nullptr)
		return;

	UAbilitySystemComponent* pAbilityComponent = Owner->GetAbilitySystemComponent();
	UObjectAttribute* pAttribute = Owner->GetAttribute();
	if (pAbilityComponent && pAttribute)
	{
		pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetHPAttribute()).Remove(HPEventHandle);
		pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetMaxHpAttribute()).Remove(MaxHPEventHandle);
		pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetMPAttribute()).Remove(MPEventHandle);
		pAbilityComponent->GetGameplayAttributeValueChangeDelegate(pAttribute->GetMaxMpAttribute()).Remove(MaxMPEventHandle);
	}
}

void UHeadHPBarWidgetBase::OnHPChanged(const FOnAttributeChangeData & CallbackData)
{

}

void UHeadHPBarWidgetBase::OnMaxHPChanged(const FOnAttributeChangeData & CallbackData)
{

}

void UHeadHPBarWidgetBase::OnMPChanged(const FOnAttributeChangeData & CallbackData)
{

}

void UHeadHPBarWidgetBase::OnMaxMPChanged(const FOnAttributeChangeData & CallbackData)
{

}
