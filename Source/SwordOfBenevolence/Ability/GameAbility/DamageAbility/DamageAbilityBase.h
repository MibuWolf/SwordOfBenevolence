// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../../AbilityTask/WaitForDamageEventTask.h"
#include "DamageAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UDamageAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UDamageAbilityBase();

public:

	// ��������
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// ���ؽ�������
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/** Called when the avatar actor is set/changes */
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:

	// ��⵱ǰʩ������ִ���ܻ�����
	bool	CheckDamage();

	// �ܻ������ص�
	UFUNCTION()
	void	OnDamageReceived(const FGameplayTag& HitTag, AActor* SourceActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TMap<FGameplayTag, UAnimMontage*> AllHitAnim;		// �����ܻ�����

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TSubclassOf<UGameplayEffect>	AutoRecover;		// �Զ��ظ�Ч��

	UWaitForDamageEventTask* Task;
};
