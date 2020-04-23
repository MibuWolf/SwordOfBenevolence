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
	UFUNCTION(BlueprintCallable,  Category = Character)
	FVector		GetDirction();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionX(float Value);
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionY(float Value);

	// ��ȡ��������HP�ٷֱ�
	UFUNCTION(BlueprintCallable,  Category = Character)
	float		GetHPPercent();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetHPPercent(float Value);

	// ��ȡ��������BUFF�ƶ�����
	UFUNCTION(BlueprintCallable,  Category = Character)
	int32		GetBuffNoMove();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetBuffNoMove(int32 Value);

	// �Ƿ������ͷż���
	UFUNCTION(BlueprintCallable, Category = Character)
	bool		IsInSkill();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetInSkill(bool Value);

	
	// �ܻ��ص�(�ܻ��߼�����ͼ�о���ʵ��)
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttacked(const FGameplayTag& DamageTags);


protected:


	void OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount);


protected:

	/** ����ϵͳ */
	UPROPERTY(VisibleAnyWhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**����*/
	UPROPERTY(EditAnywhere)
	UObjectAttribute*	Attribute;

	// װ���б�
	UPROPERTY(EditAnywhere)
	TMap<EEquipType, TSubclassOf<AGameEquip>> Equips;

protected:

	// ���ڶ������ֵĳ���
	FVector		Dirction;
	// ���ڶ������ֵ�Ѫ���ٷֱ�
	float		HPPercent;
	// ���ڶ������ֵ�BUFF�ƶ�����
	int32		Buff_NoMove;
	// ��ǰ�Ƿ����ͷż���
	bool		IsSkill;

	FDelegateHandle EventHandle;
};
