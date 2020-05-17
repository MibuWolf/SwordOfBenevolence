#include "DamageAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "../../../GameObject/GameObject.h"

UDamageAbilityBase::UDamageAbilityBase()
	:Super()
{
	// 定义不可以激活Ability的Tags 状态Tag死亡 BUFFTag眩晕
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Buff.Stun")));
	Task = nullptr;
}

void UDamageAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (Task == nullptr)
	{
		Task = UWaitForDamageEventTask::WaitForDamageEvent(this);
		Task->OnDamaged.AddDynamic(this, &UDamageAbilityBase::OnDamageReceived);
		Task->Activate();
	}

	if (AutoRecover != nullptr)
	{
		BP_ApplyGameplayEffectToOwner(AutoRecover);
	}
}

void UDamageAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	Task = nullptr;
}

void UDamageAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilitySpec & Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
}

bool UDamageAbilityBase::CheckDamage()
{
	AGameObject* GameObject = Cast<AGameObject>(GetOwningActorFromActorInfo());

	if (GameObject == nullptr || GameObject->GetAbilitySystemComponent() == nullptr)
		return false;

	FGameplayTagContainer tagContainer;
	tagContainer.AddTag(FGameplayTag::RequestGameplayTag("Status.Dead"));

	if (GameObject->GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(tagContainer))
		return false;

	return true;
}

void UDamageAbilityBase::OnDamageReceived(const FGameplayTag & HitTag, AActor * SourceActor)
{
	FGameplayAbilityActorInfo ActorInfo =  GetActorInfo();

	if (CheckDamage())
	{
		if (AllHitAnim.Contains(HitTag))
		{
			UAnimMontage* MontageToPlay = AllHitAnim[HitTag];
			UAnimInstance* AnimInstance = ActorInfo.GetAnimInstance();

			if (MontageToPlay != nullptr && AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(MontageToPlay, 1.0f);
			}
		}
	}
}
