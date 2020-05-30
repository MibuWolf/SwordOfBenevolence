// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../Ability/Attribute/ObjectAttribute.h"
#include "../Ability/GameAbilitySystemComponent.h"
#include "../GameItem/GameEquip.h"
#include "../HUD/HeadHPBarWidgetBase.h"
#include "GameObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameObjectLevelChangedHandle, const int32&, oldLevel, const int32&, NewLevel);// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams是唯一一个可以在蓝图中使用的代理
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameObjectNameChangedHandle, const FString&, oldName, const FString&, NewName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FObjectAttributeChangedHandle, const FGameplayAttribute&, Attribute, float, OldValue, float, NewValue);

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

	// 获取属性
	UObjectAttribute*		GetAttribute();

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void OnAttributeChanged(const FOnAttributeChangeData & CallbackData);

	// 死亡回调(死亡逻辑逻辑在蓝图中具体实现)
	virtual void OnDeath();

public:

	// 获取动作表现朝向
	UFUNCTION(BlueprintCallable,  Category = GameObject)
	FVector			GetDirction();

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			SetDirctionX(float Value);

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			SetDirctionY(float Value);

	// 穿上装备
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			WearEquip(AGameEquip* pEquip);
	// 脱装备
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			TakeOffEquip(EEquipType type);

	// 设置等级
	UFUNCTION(BlueprintCallable, Category = GameObject)
	virtual void	SetLevel(int32 level);

	// 获取等级
	UFUNCTION(BlueprintCallable, Category = GameObject)
	int32			GetLevel();

	// 设置名字
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			SetName(FString NewName);

	// 获取名字
	UFUNCTION(BlueprintCallable, Category = GameObject)
	FString			GetName();

	// 判定对象当前是否已经死亡
	UFUNCTION(BlueprintCallable, Category = GameObject)
	bool			IsDeath();

protected:

	void InitAllAttributeChangedHandle();

public:

	// 等级变更
	UPROPERTY(BlueprintAssignable, Category = GameObject)
	FGameObjectLevelChangedHandle LevelChangedHandle;

	// 名称变更
	UPROPERTY(BlueprintAssignable, Category = GameObject)
	FGameObjectNameChangedHandle  NameChangedHandle;

	// 属性变更
	UPROPERTY(BlueprintAssignable, Category = GameObject)
	FObjectAttributeChangedHandle AttributeChangedHandle;

protected:

	/**头顶及飘血等HUD显示组件*/
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HUDComponent;

	/** 能力系统 */
	UPROPERTY(VisibleAnywhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;
	
	// 装备列表
	UPROPERTY(EditAnywhere)
	TMap<EEquipType, TSubclassOf<AGameEquip>> EquipTypes;

	// 等级
	UPROPERTY(EditAnywhere)
	int32		Level;

	// 名字
	UPROPERTY(EditAnywhere)
	FString		Name;


protected:

	// 用于动作表现的朝向
	FVector		Dirction;

	/**属性*/
	UObjectAttribute*	Attribute = nullptr;
	
	// 当前装备的所有装备
	TMap<EEquipType, AGameEquip*> Equips;

	TMap<EAttributeType, FDelegateHandle> AllAttributeChangeHandle;

	FDelegateHandle EventHandle;

};
