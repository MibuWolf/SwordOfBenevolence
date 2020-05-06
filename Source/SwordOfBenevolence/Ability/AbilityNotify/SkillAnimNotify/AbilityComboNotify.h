// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../../AbilityInputID.h"
#include "AbilityComboNotify.generated.h"

/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UAbilityComboNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);

	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime);

	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);

public:

	UPROPERTY(EditAnywhere, Category = Ability)
	EAbilityInputID				InputID;		// °ó¶¨¿ì½Ý¼ü

};
