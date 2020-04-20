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
UCLASS()
class SWORDOFBENEVOLENCE_API UGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	UGameAbilitySystemComponent();

	// 遍历所有可能获得的能力并将可自动赋予的能力赋予给拥有者
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		AutoGiveAbilites();


public:

	virtual void AbilityLocalInputPressed(int32 InputID);

protected:


	// 当前角色所有可能拥有的能力，也就是这个MAP是该角色拥有能里的最大集合
	// 但在该Map中的能力并不意味着当前角色已经被给与GiveAbility(可能根据某些
	// 条件给与如使用道具后才拥有此能力等)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TMap<EAbilityInputID, TSubclassOf<UGameAbility>> AllPossibleAbilities;
	
	// 当前连招段数
	TMap<EAbilityInputID, int32> AbilityComboCount;			// 
};
