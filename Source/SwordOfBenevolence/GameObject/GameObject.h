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


DECLARE_MULTICAST_DELEGATE_TwoParams(FGameObjectLevelChangedHandle, const int32&, const int32&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FGameObjectNameChangedHandle, const FString&, const FString&);

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

	// 等级变更回调
	FGameObjectLevelChangedHandle		GetLevelChangeDelegate();

	// 名字变更回调
	FGameObjectNameChangedHandle		GetNameChangeDelegate();

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

	// 设置等级
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetLevel(int32 level);

	// 获取等级
	UFUNCTION(BlueprintCallable, Category = GameObject)
	int32		GetLevel();

	// 设置名字
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetName(FString NewName);

	// 获取名字
	UFUNCTION(BlueprintCallable, Category = GameObject)
	FString		GetName();

	// 受击回调(受击逻辑在蓝图中具体实现)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);


protected:


	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);

	// 基础属性更新
	void			UpdateBasicAttribute();

protected:

	/**头顶及飘血等HUD显示组件*/
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HUDComponent;

	/**头顶HUD类*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameObject|HUD")
	TSubclassOf<UHeadHPBarWidgetBase> HeadHPBarClass;

	/**头顶HUD*/
	UPROPERTY()
	UHeadHPBarWidgetBase* HeadHPBar;

	/** 能力系统 */
	UPROPERTY(VisibleAnywhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**属性*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;
	//UGDAttributeSetBase* Attribute;
	
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
	
	// 当前装备的所有装备
	TMap<EEquipType, AGameEquip*> Equips;

	FDelegateHandle EventHandle;

	FGameObjectLevelChangedHandle LevelChangedHandle;
	FGameObjectNameChangedHandle  NameChangedHandle;
};
