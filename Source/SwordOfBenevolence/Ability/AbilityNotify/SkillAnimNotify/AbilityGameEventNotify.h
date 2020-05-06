// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilityGameEventNotify.generated.h"

/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UAbilityGameEventNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

public:

	UPROPERTY(EditAnywhere, Category = Ability)
	FGameplayTag				GameplayTag;		// 触发Ability事件

	FGameplayEventData			Payload;			// 事件参数

};
