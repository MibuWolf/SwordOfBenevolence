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

	// ��ȡ����
	UObjectAttribute*		GetAttribute();

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// �ȼ�����ص�
	FGameObjectLevelChangedHandle		GetLevelChangeDelegate();

	// ���ֱ���ص�
	FGameObjectNameChangedHandle		GetNameChangeDelegate();

public:

	// ��ȡ�������ֳ���
	UFUNCTION(BlueprintCallable,  Category = GameObject)
	FVector		GetDirction();

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetDirctionX(float Value);

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetDirctionY(float Value);

	// ����װ��
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		WearEquip(AGameEquip* pEquip);
	// ��װ��
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		TakeOffEquip(EEquipType type);

	// ���õȼ�
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetLevel(int32 level);

	// ��ȡ�ȼ�
	UFUNCTION(BlueprintCallable, Category = GameObject)
	int32		GetLevel();

	// ��������
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void		SetName(FString NewName);

	// ��ȡ����
	UFUNCTION(BlueprintCallable, Category = GameObject)
	FString		GetName();

	// �ܻ��ص�(�ܻ��߼�����ͼ�о���ʵ��)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);


protected:


	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);

	// �������Ը���
	void			UpdateBasicAttribute();

protected:

	/**ͷ����ƮѪ��HUD��ʾ���*/
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HUDComponent;

	/**ͷ��HUD��*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameObject|HUD")
	TSubclassOf<UHeadHPBarWidgetBase> HeadHPBarClass;

	/**ͷ��HUD*/
	UPROPERTY()
	UHeadHPBarWidgetBase* HeadHPBar;

	/** ����ϵͳ */
	UPROPERTY(VisibleAnywhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**����*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;
	//UGDAttributeSetBase* Attribute;
	
	// װ���б�
	UPROPERTY(EditAnywhere)
	TMap<EEquipType, TSubclassOf<AGameEquip>> EquipTypes;

	// �ȼ�
	UPROPERTY(EditAnywhere)
	int32		Level;

	// ����
	UPROPERTY(EditAnywhere)
	FString		Name;

protected:

	// ���ڶ������ֵĳ���
	FVector		Dirction;
	
	// ��ǰװ��������װ��
	TMap<EEquipType, AGameEquip*> Equips;

	FDelegateHandle EventHandle;

	FGameObjectLevelChangedHandle LevelChangedHandle;
	FGameObjectNameChangedHandle  NameChangedHandle;
};
