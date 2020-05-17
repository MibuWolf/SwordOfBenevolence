// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility.h"
#include "../../GameObject/GameObject.h"
#include "../GameAbilitySystemComponent.h"

UGameAbility::UGameAbility()
	:Super()
	, AutoGive(true)
{
	// 定义不可以激活Ability的Tags 状态Tag死亡 BUFFTag眩晕
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Buff.Stun")));
}


bool UGameAbility::CanAutoGive()
{
	return AutoGive;
}

EAbilityInputID UGameAbility::GetAbilityInputID()
{
	return InputID;
}

void UGameAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	
	FGameplayTagContainer tagContainer;
	for (auto & Pair : GEGroupMap)
	{
		tagContainer.AddTag(Pair.Key);
	}
	EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(tagContainer, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UGameAbility::OnGameplayEvent));
}


void UGameAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	FGameplayTagContainer tagContainer;
	for (auto & Pair : GEGroupMap)
	{
		tagContainer.AddTag(Pair.Key);
	}

	AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(tagContainer, EventHandle);
}

void UGameAbility::OnAvatarSet(const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilitySpec & Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (AutoActive)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

int32 UGameAbility::GetSkillID() const
{
	return SkillID;
}

void UGameAbility::SetSkillLevel(int32 level)
{
	Level = level;
}

int32 UGameAbility::GetSkillLevel() const
{
	return Level;
}


void UGameAbility::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData * Payload)
{
	FGameEffectGroup* GEGroup = GEGroupMap.Find(EventTag);
	AActor* OwningActor = GetOwningActorFromActorInfo();

	if (GEGroup == nullptr || OwningActor == nullptr)
		return;

	if (GEGroup->TargetType.Get() == nullptr)
		return;

	UGETarget* TargetType = GEGroup->TargetType.GetDefaultObject();
	FGameplayAbilityTargetDataHandle targetHandle = TargetType->GetTargets(OwningActor);

	if (targetHandle.Num() <= 0)
		return;

	for (const TSubclassOf<UGameplayEffect> & GameEffect : GEGroup->GameEffectList)
	{
		BP_ApplyGameplayEffectToTarget(targetHandle, GameEffect);
	}

	FGameplayTagContainer tagContainer;
	tagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Damage"));

	if (EventTag.MatchesAny(tagContainer))
	{
		TriggerDamageEvent(EventTag, targetHandle);
	}
}

void UGameAbility::TriggerDamageEvent(FGameplayTag EventTag, FGameplayAbilityTargetDataHandle & TargetDataHandle)
{
	AActor* OwningActor = GetOwningActorFromActorInfo();

	for (TSharedPtr<FGameplayAbilityTargetData> Data : TargetDataHandle.Data)
	{
		if (Data.IsValid())
		{
			FGameplayAbilityTargetData* TargetData = Data.Get();

			if (TargetData)
			{
				for (TWeakObjectPtr<AActor> Actor : TargetData->GetActors())
				{
					AGameObject* pGameObject = Cast<AGameObject>(Actor);

					if (pGameObject)
					{
						UGameAbilitySystemComponent* GAS = Cast<UGameAbilitySystemComponent>(pGameObject->GetAbilitySystemComponent());

						if (GAS)
							GAS->OnDamage.Broadcast(EventTag, OwningActor);
					}
				}
			}
		}
	}

}
