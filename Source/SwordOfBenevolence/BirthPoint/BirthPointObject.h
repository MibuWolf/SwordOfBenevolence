// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../GameObject/GameObject.h"
#include "BirthPointObject.generated.h"


UCLASS()
class SWORDOFBENEVOLENCE_API ABirthPointObject : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ABirthPointObject();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	// 判断是否需要重新生成一个新对象
	bool	CheckAutoBirthNewObject();

	// 自动生成新对象，每帧执行
	void	AutoSpwanGameObject(float DeltaTime);

public:

	// 生成新的对象
	UFUNCTION(BlueprintCallable, Category = BirthPoint)
	void	SpwanNewGameObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// 所有可能刷新的物资及刷新概率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BirthPoint)
	TMap<TSubclassOf<AGameObject>, int32> AllPossibleObject;

	// 是否自动刷新
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BirthPoint)
	bool			AutoBirth;

	// 自动刷新CD时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BirthPoint)
	float			CDTime;

protected:

	AGameObject*				CurrentObject;

	float						WaitTime;

};
