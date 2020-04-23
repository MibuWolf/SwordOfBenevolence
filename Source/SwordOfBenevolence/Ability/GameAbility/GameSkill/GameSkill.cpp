// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSkill.h"
#include "Animation/AnimInstance.h"
#include "AbilitySystemComponent.h"



UGameSkill::UGameSkill()
	:Super()
{
	// 定义激活技能时设置状态标签State.Skill
	//ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Skill")));
}

void UGameSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	if (MontageToPlay != nullptr && AnimInstance != nullptr)
	{
		TArray<FActiveGameplayEffectHandle>	AppliedEffects;

		float const Duration = AnimInstance->Montage_Play(MontageToPlay, PlayRate);
		IsPlaying = true;

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UGameSkill::OnMontageEnded);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, MontageToPlay);

		if (SectionName != NAME_None)
		{
			AnimInstance->Montage_JumpToSection(SectionName);
		}
	}
}

void UGameSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsPlaying)
		StopMontage();

	//FString ComboTag = FString::Printf(TEXT("Ability.Skill.Combo.%d"), InputID);
	FGameplayTagContainer tagContainer;
	//tagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(*ComboTag)));

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystemComponent && AbilitySystemComponent->HasAnyMatchingGameplayTags(tagContainer))
	{
		AbilitySystemComponent->RemoveLooseGameplayTags(tagContainer);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UGameSkill::OnMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	IsPlaying = false;
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UGameSkill::StopMontage()
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	if (!ActorInfo)
	{
		return false;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		return false;
	}

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	// Check if the montage is still playing
	// The ability would have been interrupted, in which case we should automatically stop the montage
	if (AbilitySystemComponent)
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == this
			&& AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			// Unbind delegates so they don't get called as well
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}

	return false;
}
