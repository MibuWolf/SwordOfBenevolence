// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GETarget/GETarget.h"
#include "GameEffectGroup.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct SWORDOFBENEVOLENCE_API FGameEffectGroup
{
	GENERATED_BODY()

public:

	FGameEffectGroup() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TSubclassOf<UGETarget> TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<TSubclassOf<UGameplayEffect>> GameEffectList;

};
