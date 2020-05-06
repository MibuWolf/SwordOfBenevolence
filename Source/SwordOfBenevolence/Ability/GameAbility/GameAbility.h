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

	// 激活能力
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// 重载结束能力
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/** Called when the avatar actor is set/changes */
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:

	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

protected:

	UPROPERTY(EditAnywhere, Category = Ability)
	int32				SkillID;		// 技能ID

	UPROPERTY(EditAnywhere, Category = Ability)
	int32				Level;			// 技能等级

	UPROPERTY(EditAnywhere, Category = Ability)
	EAbilityInputID		InputID;		// 绑定按键

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				AutoGive;		// 是否默认拥有此能力

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				AutoActive;		// 在赋予此能力时是否自动激活

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TMap<FGameplayTag, FGameEffectGroup> GEGroupMap;	// 所有效果

	FDelegateHandle		EventHandle;	// GameplayEvent回调Handle
};
