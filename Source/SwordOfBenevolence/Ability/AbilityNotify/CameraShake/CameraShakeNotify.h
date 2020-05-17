// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CameraShakeNotify.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UCameraShakeNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

public:

	UPROPERTY(EditAnywhere, Category = Ability)
	TSubclassOf<class UCameraShake>				GameraShake;		// �����

	UPROPERTY(EditAnywhere, Category = Ability)
	float				InnerRadius;		// ����ڶ���ģ��λ�þ���InnerRadius  OuterRadius֮��ʱ����Ӧ����

	UPROPERTY(EditAnywhere, Category = Ability)
	float				OuterRadius;		// ����ڶ���ģ��λ�þ���InnerRadius  OuterRadius֮��ʱ����Ӧ����

	UPROPERTY(EditAnywhere, Category = Ability)
	float				Falloff;			// �����OuterRadius������˥��ϵ��

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				TowardsMesh;		//  �Ƿ���Ҫѡ����ʹ�䳯��ģ��
};
