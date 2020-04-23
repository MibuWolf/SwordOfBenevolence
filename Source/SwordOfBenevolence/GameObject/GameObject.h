// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../Ability/Attribute/ObjectAttribute.h"
#include "../Ability/GameAbilitySystemComponent.h"
#include "../GameItem/GameEquip.h"
#include "GameObject.generated.h"

UCLASS()
class SWORDOFBENEVOLENCE_API AGameObject : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:

	// 获取动作表现朝向
	UFUNCTION(BlueprintCallable,  Category = Character)
	FVector		GetDirction();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionX(float Value);
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionY(float Value);

	// 获取动作表现HP百分比
	UFUNCTION(BlueprintCallable,  Category = Character)
	float		GetHPPercent();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetHPPercent(float Value);

	// 获取动作表现BUFF移动限制
	UFUNCTION(BlueprintCallable,  Category = Character)
	int32		GetBuffNoMove();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetBuffNoMove(int32 Value);

	// 是否正在释放技能
	UFUNCTION(BlueprintCallable, Category = Character)
	bool		IsInSkill();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetInSkill(bool Value);

	
	// 受击回调(受击逻辑在蓝图中具体实现)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);


protected:


	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);


protected:

	/** 能力系统 */
	UPROPERTY(VisibleAnyWhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**属性*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;

	// 装备列表
	UPROPERTY(EditAnywhere)
	TMap<EEquipType, TSubclassOf<AGameEquip>> Equips;

protected:

	// 用于动作表现的朝向
	FVector		Dirction;
	// 用于动作表现的血量百分比
	float		HPPercent;
	// 用于动作表现的BUFF移动限制
	int32		Buff_NoMove;
	// 当前是否在释放技能
	bool		IsSkill;

	FDelegateHandle EventHandle;
};
