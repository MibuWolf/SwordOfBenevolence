// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSkill.h"
#include "Animation/AnimInstance.h"
#include "AbilitySystemComponent.h"
#include "../../../GamePlay/SOBGameInstance.h"
#include "../../../DataTable/SkillTableData.h"
#include "../../../DataTable/AttributeTableData.h"


UGameSkill::UGameSkill()
	:Super()
{
	// ���弤���ʱ����״̬��ǩState.Skill
	//ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Skill")));
}

void UGameSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	if (bHasBlueprintActivate)
	{
		// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
		K2_ActivateAbility();
	}
	else if (bHasBlueprintActivateFromEvent)
	{
		if (TriggerEventData)
		{
			// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
			K2_ActivateAbilityFromEvent(*TriggerEventData);
		}
		else
		{
			UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use Activate Ability instead of Activate Ability From Event."), *GetName());
			bool bReplicateEndAbility = false;
			bool bWasCancelled = true;
			EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		}
	}
	else
	{
		// Native child classes may want to override ActivateAbility and do something like this:

		// Do stuff...

		if (CommitAbility(Handle, ActorInfo, ActivationInfo))		// ..then commit the ability...
		{

			UpdateAttribute();

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

void UGameSkill::SetSkillLevel(int32 level)
{
	Super::SetSkillLevel(level);

	UpdateAttribute();
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

void UGameSkill::UpdateAttribute()
{
	UWorld* pWorld = GetWorld();
	if (!pWorld)
		return;

	USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

	if (pGameInstance == nullptr)
		return;

	FString strID = FString::FromInt(SkillID);
	FSkillTableData* pSkill = pGameInstance->GetSkillTableData(strID);

	if (pSkill == nullptr)
		return;

	FString strLevel = FString::FromInt(Level);
	FString attributeID = pSkill->AttributeID + strLevel;

	FAttributeTableData* pAttribute = pGameInstance->GetAttributeTableData(attributeID);

	if (pAttribute == nullptr)
		return;

	PlayRate = float(pAttribute->SPD) / 100.0f;
}
