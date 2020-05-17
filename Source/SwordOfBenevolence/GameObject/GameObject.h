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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameObjectLevelChangedHandle, const int32&, oldLevel, const int32&, NewLevel);// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams��Ψһһ����������ͼ��ʹ�õĴ���
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

	// ��ȡ����
	UObjectAttribute*		GetAttribute();

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void OnAttributeChanged(const FOnAttributeChangeData & CallbackData);

public:

	// ��ȡ�������ֳ���
	UFUNCTION(BlueprintCallable,  Category = GameObject)
	FVector			GetDirction();

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			SetDirctionX(float Value);

	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			SetDirctionY(float Value);

	// ����װ��
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			WearEquip(AGameEquip* pEquip);
	// ��װ��
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			TakeOffEquip(EEquipType type);

	// ���õȼ�
	UFUNCTION(BlueprintCallable, Category = GameObject)
	virtual void	SetLevel(int32 level);

	// ��ȡ�ȼ�
	UFUNCTION(BlueprintCallable, Category = GameObject)
	int32			GetLevel();

	// ��������
	UFUNCTION(BlueprintCallable, Category = GameObject)
	void			SetName(FString NewName);

	// ��ȡ����
	UFUNCTION(BlueprintCallable, Category = GameObject)
	FString			GetName();

	// �ܻ��ص�(�ܻ��߼�����ͼ�о���ʵ��)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);

protected:

	void InitAllAttributeChangedHandle();

	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);


public:

	// �ȼ����
	UPROPERTY(BlueprintAssignable, Category = GameObject)
	FGameObjectLevelChangedHandle LevelChangedHandle;

	// ���Ʊ��
	UPROPERTY(BlueprintAssignable, Category = GameObject)
	FGameObjectNameChangedHandle  NameChangedHandle;

	// ���Ա��
	UPROPERTY(BlueprintAssignable, Category = GameObject)
	FObjectAttributeChangedHandle AttributeChangedHandle;

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

	/**����*/
	UObjectAttribute*	Attribute;
	
	// ��ǰװ��������װ��
	TMap<EEquipType, AGameEquip*> Equips;

	TMap<EAttributeType, FDelegateHandle> AllAttributeChangeHandle;

	FDelegateHandle EventHandle;

};
