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
	UFUNCTION(BlueprintCallable,  Category = GameObject)
	FVector		GetDirction();
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetDirctionX(float Value);
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetDirctionY(float Value);
	// 穿上装备
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		WearEquip(AGameEquip* pEquip);
	// 脱装备
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		TakeOffEquip(EEquipType type);

	// 受击回调(受击逻辑在蓝图中具体实现)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);


protected:


	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);


protected:

	/**头顶及飘血等HUD显示组件*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GameObject|HUD")
	class UWidgetComponent* HUDComponent;

	/** 能力系统 */
	UPROPERTY(VisibleAnyWhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**属性*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;

	// 装备列表
	UPROPERTY(EditAnywhere)
	TMap<EEquipType, TSubclassOf<AGameEquip>> EquipTypes;

protected:

	// 用于动作表现的朝向
	FVector		Dirction;
	
	// 当前装备的所有装备
	TMap<EEquipType, AGameEquip*> Equips;

	FDelegateHandle EventHandle;

};
