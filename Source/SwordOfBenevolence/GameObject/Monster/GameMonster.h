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

	// 初始化属性
	void			InitMonsterAttribute();

	// 定时延迟销毁回调
	void			OnDelayDestory();

public:


	virtual void			OnDeath();

protected:

	// 怪物ID
	UPROPERTY(EditAnywhere)
	FString		MonsterID;

};
