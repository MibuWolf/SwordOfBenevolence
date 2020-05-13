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

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "STR")
	FGameplayAttributeData STR;
	ATTRIBUTE_ACCESSORS(UGameAttribute, STR)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "VIT")
	FGameplayAttributeData VIT;
	ATTRIBUTE_ACCESSORS(UGameAttribute, VIT)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "TEN")
	FGameplayAttributeData TEN;
	ATTRIBUTE_ACCESSORS(UGameAttribute, TEN)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "AGI")
	FGameplayAttributeData AGI;
	ATTRIBUTE_ACCESSORS(UGameAttribute, AGI)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "WIS")
	FGameplayAttributeData WIS;
	ATTRIBUTE_ACCESSORS(UGameAttribute, WIS)

	/** ��־ */
	UPROPERTY(BlueprintReadOnly, Category = "WIL")
	FGameplayAttributeData WIL;
	ATTRIBUTE_ACCESSORS(UGameAttribute, WIL)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "SPT")
	FGameplayAttributeData SPT;
	ATTRIBUTE_ACCESSORS(UGameAttribute, SPT)

	/** רע */
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
