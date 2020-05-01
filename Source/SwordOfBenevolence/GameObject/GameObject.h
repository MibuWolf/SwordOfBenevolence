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

	// �ܻ��ص�(�ܻ��߼�����ͼ�о���ʵ��)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);


protected:


	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);


protected:

	/**ͷ����ƮѪ��HUD��ʾ���*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GameObject|HUD")
	class UWidgetComponent* HUDComponent;

	/** ����ϵͳ */
	UPROPERTY(VisibleAnyWhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**����*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;

	// װ���б�
	UPROPERTY(EditAnywhere)
	TMap<EEquipType, TSubclassOf<AGameEquip>> EquipTypes;

protected:

	// ���ڶ������ֵĳ���
	FVector		Dirction;
	
	// ��ǰװ��������װ��
	TMap<EEquipType, AGameEquip*> Equips;

	FDelegateHandle EventHandle;

};
