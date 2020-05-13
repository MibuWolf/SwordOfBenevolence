// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectAttribute.h"
#include "PlayerAttribute.generated.h"


/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UPlayerAttribute : public UObjectAttribute
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	UPlayerAttribute();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "STR")
	FGameplayAttributeData STR;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, STR)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "VIT")
	FGameplayAttributeData VIT;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, VIT)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "TEN")
	FGameplayAttributeData TEN;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, TEN)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "AGI")
	FGameplayAttributeData AGI;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, AGI)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "WIS")
	FGameplayAttributeData WIS;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, WIS)

	/** ��־ */
	UPROPERTY(BlueprintReadOnly, Category = "WIL")
	FGameplayAttributeData WIL;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, WIL)

	/** ���� */
	UPROPERTY(BlueprintReadOnly, Category = "SPT")
	FGameplayAttributeData SPT;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, SPT)

	/** רע */
	UPROPERTY(BlueprintReadOnly, Category = "CTN")
	FGameplayAttributeData CTN;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, CTN)


public:

	// ������ҵȼ���ʼ������
	void	InitializeByPlayerLevel(int32 level);

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
