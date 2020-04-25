// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameItem.h"
#include "../Ability/Attribute/ObjectAttribute.h"
#include "GameEquip.generated.h"

class AGameObject;

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	// 0 Hair
	Hair				UMETA(DisplayName = "Hair"),
	// 1 Breastplate
	Breastplate			UMETA(DisplayName = "Breastplate"),
	// 2 Hand
	Hand				UMETA(DisplayName = "Hand"),
	// 3 Pants
	Pants				UMETA(DisplayName = "Pants"),
	// 4 Shoes
	Shoes				UMETA(DisplayName = "Shoes"),
	// 5 MainWeapon
	MainWeapon			UMETA(DisplayName = "MainWeapon"),
	// 6 SubWeapon
	SubWeapon			UMETA(DisplayName = "SubWeapon"),
};

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API AGameEquip : public AGameItem
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this character's properties
	AGameEquip();

public:

	// 获取装备类型
	UFUNCTION(BlueprintCallable, Category = Equip)
	EEquipType					GetEquipType();
	// 获取装备槽名称
	UFUNCTION(BlueprintCallable, Category = Equip)
	FName						GetSocketName();
	// 获取绑定规则
	FAttachmentTransformRules	GetAttachmentRules();
	// 获取装备属性
	UFUNCTION(BlueprintCallable, Category = Equip)
	UObjectAttribute*			GetAttribute();


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, Category = Equip)
	EEquipType		EquipType;			// 装备类型

	UPROPERTY(EditAnywhere, Category = Equip)
	EAttachmentRule LocationRule;		// 位置规则

	UPROPERTY(EditAnywhere, Category = Equip)
	EAttachmentRule RotationRule;		// 旋转规则

	UPROPERTY(EditAnywhere, Category = Equip)
	EAttachmentRule ScaleRule;			// 缩放规则

	UPROPERTY(EditAnywhere, Category = Equip)
	bool bWeldSimulatedBodies;

	/**属性*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;

};
