// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInputID.h"
#include "AbilitySystemComponent.h"
#include "GameAbility/GameAbility.h"
#include "GameAbilitySystemComponent.generated.h"


/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageDelegate, const FGameplayTag&, HitTag, AActor*, SourceActor);

UCLASS()
class SWORDOFBENEVOLENCE_API UGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	UGameAbilitySystemComponent();

	// 遍历所有可能获得的能力并将可自动赋予的能力赋予给拥有者
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		AutoGiveAbilites();

	// 根据技能ID添加技能
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		AddSkill(int32 skillID);

	// 随机释放一个技能
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		RandomActivateAbility();

public:

	virtual void AbilityLocalInputPressed(int32 InputID);

public:

	// 设置某按键能力是否可以响应连招
	void		SetAbilityResponseCombo(EAbilityInputID InputID, bool canResponse);

protected:

	// 根据绑定的输入ID获取绑定在该输入上的能力个数（Combo个数）
	int32		GetAbilityCountByInputID(EAbilityInputID InputID);

public:

	FOnDamageDelegate OnDamage;

protected:

	// 当前角色拥有的能力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TMap<int32, TSubclassOf<UGameAbility>> AllPossibleAbilities;

	// 当前角色被击能力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TSubclassOf<UGameplayAbility>		BeHitAbility;
	
	// 当前连招段数
	TMap<EAbilityInputID, int32> AbilityComboCount;			
	// 当前是否相应连招
	TMap<EAbilityInputID, bool> ResponseCombo;

};
