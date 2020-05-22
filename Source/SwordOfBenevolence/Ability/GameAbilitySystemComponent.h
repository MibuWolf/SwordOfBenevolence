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

	// �������п��ܻ�õ������������Զ���������������ӵ����
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		AutoGiveAbilites();

	// ���ݼ���ID��Ӽ���
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		AddSkill(int32 skillID);

	// ����ͷ�һ������
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		RandomActivateAbility();

public:

	virtual void AbilityLocalInputPressed(int32 InputID);

public:

	// ����ĳ���������Ƿ������Ӧ����
	void		SetAbilityResponseCombo(EAbilityInputID InputID, bool canResponse);

protected:

	// ���ݰ󶨵�����ID��ȡ���ڸ������ϵ�����������Combo������
	int32		GetAbilityCountByInputID(EAbilityInputID InputID);

public:

	FOnDamageDelegate OnDamage;

protected:

	// ��ǰ��ɫӵ�е�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TMap<int32, TSubclassOf<UGameAbility>> AllPossibleAbilities;

	// ��ǰ��ɫ��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TSubclassOf<UGameplayAbility>		BeHitAbility;
	
	// ��ǰ���ж���
	TMap<EAbilityInputID, int32> AbilityComboCount;			
	// ��ǰ�Ƿ���Ӧ����
	TMap<EAbilityInputID, bool> ResponseCombo;

};
