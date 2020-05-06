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
	SetMaxHP(pAttribute->MaxHp.GetCurrentValue());
	SetCurrentHP(pAttribute->HP.GetCurrentValue());
	SetCurrentMP(pAttribute->MP.GetCurrentValue());
	SetMaxMP(pAttribute->MaxMp.GetCurrentValue());

	LevelHandle = Owner->GetLevelChangeDelegate().AddUObject(this, &UHeadHPBarWidgetBase::OnLevelChanged);
	NameHandle = Owner->GetNameChangeDelegate().AddUObject(this, &UHeadHPBarWidgetBase::OnNameChanged);
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

	Owner->GetLevelChangeDelegate().Remove(LevelHandle);
	Owner->GetNameChangeDelegate().Remove(NameHandle);
}

void UHeadHPBarWidgetBase::OnLevelChanged(const int32 & oldLevel, const int32 & newLevel)
{
	SetLevel(newLevel);
}

void UHeadHPBarWidgetBase::OnNameChanged(const FString & oldName, const FString & newName)
{
	SetName(newName);
}

void UHeadHPBarWidgetBase::OnHPChanged(const FOnAttributeChangeData & CallbackData)
{
	SetCurrentHP(CallbackData.NewValue);
}

void UHeadHPBarWidgetBase::OnMaxHPChanged(const FOnAttributeChangeData & CallbackData)
{
	SetMaxHP(CallbackData.NewValue);
}

void UHeadHPBarWidgetBase::OnMPChanged(const FOnAttributeChangeData & CallbackData)
{
	SetCurrentMP(CallbackData.NewValue);
}

void UHeadHPBarWidgetBase::OnMaxMPChanged(const FOnAttributeChangeData & CallbackData)
{
	SetMaxMP(CallbackData.NewValue);
}
