// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameObject.h"
#include "GameMonster.generated.h"

/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API AGameMonster : public AGameObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameMonster();

protected:
	
	// Called when the game starts or when spawned
	virtual void	BeginPlay() override;

	// ��ʼ������
	void			InitMonsterAttribute();

	// ��ʱ�ӳ����ٻص�
	void			OnDelayDestory();

public:


	virtual void			OnDeath();

protected:

	// ����ID
	UPROPERTY(EditAnywhere)
	FString		MonsterID;

};
