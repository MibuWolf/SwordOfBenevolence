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

	// 激活能力
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// 重载结束能力
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/** Called when the avatar actor is set/changes */
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:

	// 检测当前施法可以执行受击动作
	bool	CheckDamage();

	// 受击动作回调
	UFUNCTION()
	void	OnDamageReceived(const FGameplayTag& HitTag, AActor* SourceActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TMap<FGameplayTag, UAnimMontage*> AllHitAnim;		// 所有受击动作

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TSubclassOf<UGameplayEffect>	AutoRecover;		// 自动回复效果

	UWaitForDamageEventTask* Task;
};
