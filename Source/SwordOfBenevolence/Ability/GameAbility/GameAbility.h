// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../AbilityInputID.h"
#include "../GameEffect/GameEffectGroup.h"
#include "GameAbility.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UGameAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UGameAbility();

	bool				CanAutoGive();

	EAbilityInputID		GetAbilityInputID();

public:

	// ��������
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// ���ؽ�������
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/** Called when the avatar actor is set/changes */
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

public:

	// ���õ�ǰ����ID
	UFUNCTION(BlueprintCallable, Category = GameObject)
	int32		GetSkillID() const;

	// ���õ�ǰ���ܵȼ�
	UFUNCTION(BlueprintCallable, Category = GameObject)
	virtual void		SetSkillLevel(int32 level);

	// ���õ�ǰ���ܵȼ�
	UFUNCTION(BlueprintCallable, Category = GameObject)
	int32		GetSkillLevel() const;

protected:

	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	void TriggerDamageEvent(FGameplayTag EventTag, FGameplayAbilityTargetDataHandle& TargetData);

protected:

	UPROPERTY(EditAnywhere, Category = Ability)
	int32				SkillID;		// ����ID

	UPROPERTY(EditAnywhere, Category = Ability)
	int32				Level;			// ���ܵȼ�

	UPROPERTY(EditAnywhere, Category = Ability)
	EAbilityInputID		InputID;		// �󶨰���

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				AutoGive;		// �Ƿ�Ĭ��ӵ�д�����

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				AutoActive;		// �ڸ��������ʱ�Ƿ��Զ�����

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TMap<FGameplayTag, FGameEffectGroup> GEGroupMap;	// ����Ч��

	FDelegateHandle		EventHandle;	// GameplayEvent�ص�Handle
};
