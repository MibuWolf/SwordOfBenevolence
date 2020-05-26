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

	// �ж��Ƿ���Ҫ��������һ���¶���
	bool	CheckAutoBirthNewObject();

	// �Զ������¶���ÿִ֡��
	void	AutoSpwanGameObject(float DeltaTime);

public:

	// �����µĶ���
	UFUNCTION(BlueprintCallable, Category = BirthPoint)
	void	SpwanNewGameObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// ���п���ˢ�µ����ʼ�ˢ�¸���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BirthPoint)
	TMap<TSubclassOf<AGameObject>, int32> AllPossibleObject;

	// �Ƿ��Զ�ˢ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BirthPoint)
	bool			AutoBirth;

	// �Զ�ˢ��CDʱ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BirthPoint)
	float			CDTime;

protected:

	AGameObject*				CurrentObject;

	float						WaitTime;

};
