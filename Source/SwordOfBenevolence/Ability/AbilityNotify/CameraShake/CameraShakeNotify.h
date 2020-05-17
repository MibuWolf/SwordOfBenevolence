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
	TSubclassOf<class UCameraShake>				GameraShake;		// 相机震动

	UPROPERTY(EditAnywhere, Category = Ability)
	float				InnerRadius;		// 相机在动作模型位置距离InnerRadius  OuterRadius之间时才响应震屏

	UPROPERTY(EditAnywhere, Category = Ability)
	float				OuterRadius;		// 相机在动作模型位置距离InnerRadius  OuterRadius之间时才响应震屏

	UPROPERTY(EditAnywhere, Category = Ability)
	float				Falloff;			// 相机在OuterRadius附近的衰减系数

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				TowardsMesh;		//  是否需要选择震动使其朝向模型
};
