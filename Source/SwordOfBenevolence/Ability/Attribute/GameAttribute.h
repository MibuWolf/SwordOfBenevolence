// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeType.h"
#include "GameAttribute.generated.h"



/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UGameAttribute : public UAttributeSet
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	UGameAttribute();

public:

	/** 力量 */
	UPROPERTY(BlueprintReadOnly, Category = "STR")
	FGameplayAttributeData STR;
	ATTRIBUTE_ACCESSORS(UGameAttribute, STR)

	/** 耐力 */
	UPROPERTY(BlueprintReadOnly, Category = "VIT")
	FGameplayAttributeData VIT;
	ATTRIBUTE_ACCESSORS(UGameAttribute, VIT)

	/** 韧性 */
	UPROPERTY(BlueprintReadOnly, Category = "TEN")
	FGameplayAttributeData TEN;
	ATTRIBUTE_ACCESSORS(UGameAttribute, TEN)

	/** 敏捷 */
	UPROPERTY(BlueprintReadOnly, Category = "AGI")
	FGameplayAttributeData AGI;
	ATTRIBUTE_ACCESSORS(UGameAttribute, AGI)

	/** 智力 */
	UPROPERTY(BlueprintReadOnly, Category = "WIS")
	FGameplayAttributeData WIS;
	ATTRIBUTE_ACCESSORS(UGameAttribute, WIS)

	/** 意志 */
	UPROPERTY(BlueprintReadOnly, Category = "WIL")
	FGameplayAttributeData WIL;
	ATTRIBUTE_ACCESSORS(UGameAttribute, WIL)

	/** 精神 */
	UPROPERTY(BlueprintReadOnly, Category = "SPT")
	FGameplayAttributeData SPT;
	ATTRIBUTE_ACCESSORS(UGameAttribute, SPT)

	/** 专注 */
	UPROPERTY(BlueprintReadOnly, Category = "CTN")
	FGameplayAttributeData CTN;
	ATTRIBUTE_ACCESSORS(UGameAttribute, CTN)

protected:

	/*UFUNCTION()
	virtual void OnRep_HP();

	UFUNCTION()
	virtual void OnRep_MaxHP();

	UFUNCTION()
	virtual void OnRep_MP();

	UFUNCTION()
	virtual void OnRep_MaxMP();*/


};
